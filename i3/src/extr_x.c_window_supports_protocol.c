#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_window_t ;
struct TYPE_4__ {size_t atoms_len; scalar_t__* atoms; } ;
typedef  TYPE_1__ xcb_icccm_get_wm_protocols_reply_t ;
typedef  int /*<<< orphan*/  xcb_get_property_cookie_t ;
typedef  scalar_t__ xcb_atom_t ;
typedef  size_t uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_WM_PROTOCOLS ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  xcb_icccm_get_wm_protocols (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xcb_icccm_get_wm_protocols_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_icccm_get_wm_protocols_reply_wipe (TYPE_1__*) ; 

bool window_supports_protocol(xcb_window_t window, xcb_atom_t atom) {
    xcb_get_property_cookie_t cookie;
    xcb_icccm_get_wm_protocols_reply_t protocols;
    bool result = false;

    cookie = xcb_icccm_get_wm_protocols(conn, window, A_WM_PROTOCOLS);
    if (xcb_icccm_get_wm_protocols_reply(conn, cookie, &protocols, NULL) != 1)
        return false;

    /* Check if the client’s protocols have the requested atom set */
    for (uint32_t i = 0; i < protocols.atoms_len; i++)
        if (protocols.atoms[i] == atom)
            result = true;

    xcb_icccm_get_wm_protocols_reply_wipe(&protocols);

    return result;
}