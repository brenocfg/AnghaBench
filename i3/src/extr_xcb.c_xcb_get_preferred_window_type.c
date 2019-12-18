#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int format; } ;
typedef  TYPE_1__ xcb_get_property_reply_t ;
typedef  scalar_t__ xcb_atom_t ;

/* Variables and functions */
 scalar_t__ A__NET_WM_WINDOW_TYPE_DIALOG ; 
 scalar_t__ A__NET_WM_WINDOW_TYPE_DROPDOWN_MENU ; 
 scalar_t__ A__NET_WM_WINDOW_TYPE_MENU ; 
 scalar_t__ A__NET_WM_WINDOW_TYPE_NORMAL ; 
 scalar_t__ A__NET_WM_WINDOW_TYPE_NOTIFICATION ; 
 scalar_t__ A__NET_WM_WINDOW_TYPE_POPUP_MENU ; 
 scalar_t__ A__NET_WM_WINDOW_TYPE_SPLASH ; 
 scalar_t__ A__NET_WM_WINDOW_TYPE_TOOLBAR ; 
 scalar_t__ A__NET_WM_WINDOW_TYPE_TOOLTIP ; 
 scalar_t__ A__NET_WM_WINDOW_TYPE_UTILITY ; 
 scalar_t__ XCB_NONE ; 
 scalar_t__* xcb_get_property_value (TYPE_1__*) ; 
 int xcb_get_property_value_length (TYPE_1__*) ; 

xcb_atom_t xcb_get_preferred_window_type(xcb_get_property_reply_t *reply) {
    if (reply == NULL || xcb_get_property_value_length(reply) == 0)
        return XCB_NONE;

    xcb_atom_t *atoms;
    if ((atoms = xcb_get_property_value(reply)) == NULL)
        return XCB_NONE;

    for (int i = 0; i < xcb_get_property_value_length(reply) / (reply->format / 8); i++) {
        if (atoms[i] == A__NET_WM_WINDOW_TYPE_NORMAL ||
            atoms[i] == A__NET_WM_WINDOW_TYPE_DIALOG ||
            atoms[i] == A__NET_WM_WINDOW_TYPE_UTILITY ||
            atoms[i] == A__NET_WM_WINDOW_TYPE_TOOLBAR ||
            atoms[i] == A__NET_WM_WINDOW_TYPE_SPLASH ||
            atoms[i] == A__NET_WM_WINDOW_TYPE_MENU ||
            atoms[i] == A__NET_WM_WINDOW_TYPE_DROPDOWN_MENU ||
            atoms[i] == A__NET_WM_WINDOW_TYPE_POPUP_MENU ||
            atoms[i] == A__NET_WM_WINDOW_TYPE_TOOLTIP ||
            atoms[i] == A__NET_WM_WINDOW_TYPE_NOTIFICATION) {
            return atoms[i];
        }
    }

    return XCB_NONE;
}