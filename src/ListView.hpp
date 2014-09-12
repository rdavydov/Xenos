#pragma once

#include "Control.hpp"

#include <initializer_list>

namespace ctrl
{

class ListView : public Control
{
public:
    ListView( HWND hwnd = NULL )
        : Control( hwnd )  {  }

    virtual void AddColumn( const std::wstring& name, int width, int iSubItem = 0 )
    {
        LVCOLUMNW lvc = { 0 };

        lvc.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
        lvc.pszText = (LPWSTR)name.c_str();
        lvc.iSubItem = iSubItem;
        lvc.cx = width;

        ListView_InsertColumn( _hwnd, iSubItem, &lvc );
    }

    virtual void AddItem( const std::wstring& text, LPARAM lParam, const std::initializer_list<std::wstring>& args = { } )
    {
        LVITEMW lvi = { 0 };

        lvi.mask = LVIF_TEXT | LVIF_PARAM;

        lvi.pszText = (LPWSTR)text.c_str();
        lvi.cchTextMax = static_cast<int>(text.length()) + 1;
        lvi.lParam = lParam;

        int pos = ListView_InsertItem( _hwnd, &lvi );

        for (size_t i = 0; i < args.size(); i++)
            ListView_SetItemText( _hwnd, pos, (int)(i + 1), (LPWSTR)(args.begin() + i)->c_str() );
    }


    virtual std::wstring itemText( int idx, int iSubItem = 0 )
    {
        wchar_t buf[256] = { 0 };
        ListView_GetItemText( _hwnd, idx, iSubItem, buf, ARRAYSIZE( buf ) );

        return buf;
    }

    virtual inline int selection() const { return ListView_GetNextItem( _hwnd, 0, LVNI_SELECTED ); }

    virtual inline void reset() { ListView_DeleteAllItems( _hwnd ); }
};

}