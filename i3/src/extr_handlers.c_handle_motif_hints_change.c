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
typedef  int /*<<< orphan*/  xcb_window_t ;
typedef  int /*<<< orphan*/  xcb_get_property_reply_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;
typedef  int /*<<< orphan*/  xcb_atom_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ border_style_t ;
struct TYPE_5__ {scalar_t__ border_style; int /*<<< orphan*/  current_border_width; int /*<<< orphan*/ * window; } ;
typedef  TYPE_1__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  A__MOTIF_WM_HINTS ; 
 scalar_t__ BS_NORMAL ; 
 int /*<<< orphan*/  DLOG (char*,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  XCB_GET_PROPERTY_TYPE_ANY ; 
 TYPE_1__* con_by_window_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  con_set_border_style (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  croot ; 
 int /*<<< orphan*/  window_update_motif_hints (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  x_push_changes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xcb_get_property_reply (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_get_property_unchecked (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool handle_motif_hints_change(void *data, xcb_connection_t *conn, uint8_t state, xcb_window_t window,
                                      xcb_atom_t name, xcb_get_property_reply_t *prop) {
    Con *con;
    if ((con = con_by_window_id(window)) == NULL || con->window == NULL)
        return false;

    if (prop == NULL) {
        prop = xcb_get_property_reply(conn, xcb_get_property_unchecked(conn, false, window, A__MOTIF_WM_HINTS, XCB_GET_PROPERTY_TYPE_ANY, 0, 5 * sizeof(uint64_t)),
                                      NULL);

        if (prop == NULL)
            return false;
    }

    border_style_t motif_border_style;
    window_update_motif_hints(con->window, prop, &motif_border_style);

    if (motif_border_style != con->border_style && motif_border_style != BS_NORMAL) {
        DLOG("Update border style of con %p to %d\n", con, motif_border_style);
        con_set_border_style(con, motif_border_style, con->current_border_width);

        x_push_changes(croot);
    }

    return true;
}