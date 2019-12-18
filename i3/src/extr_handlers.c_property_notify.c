#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_window_t ;
typedef  int /*<<< orphan*/  xcb_get_property_reply_t ;
typedef  int /*<<< orphan*/  xcb_get_property_cookie_t ;
typedef  scalar_t__ xcb_atom_t ;
typedef  scalar_t__ uint8_t ;
struct property_handler_t {scalar_t__ atom; int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ;int /*<<< orphan*/  long_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ *) ; 
 size_t NUM_HANDLERS ; 
 int /*<<< orphan*/  XCB_GET_PROPERTY_TYPE_ANY ; 
 scalar_t__ XCB_PROPERTY_DELETE ; 
 int /*<<< orphan*/  conn ; 
 struct property_handler_t* property_handlers ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_get_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xcb_get_property_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void property_notify(uint8_t state, xcb_window_t window, xcb_atom_t atom) {
    struct property_handler_t *handler = NULL;
    xcb_get_property_reply_t *propr = NULL;

    for (size_t c = 0; c < NUM_HANDLERS; c++) {
        if (property_handlers[c].atom != atom)
            continue;

        handler = &property_handlers[c];
        break;
    }

    if (handler == NULL) {
        //DLOG("Unhandled property notify for atom %d (0x%08x)\n", atom, atom);
        return;
    }

    if (state != XCB_PROPERTY_DELETE) {
        xcb_get_property_cookie_t cookie = xcb_get_property(conn, 0, window, atom, XCB_GET_PROPERTY_TYPE_ANY, 0, handler->long_len);
        propr = xcb_get_property_reply(conn, cookie, 0);
    }

    /* the handler will free() the reply unless it returns false */
    if (!handler->cb(NULL, conn, state, window, atom, propr))
        FREE(propr);
}