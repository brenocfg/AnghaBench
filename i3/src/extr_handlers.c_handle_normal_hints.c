#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_window_t ;
typedef  int /*<<< orphan*/  xcb_get_property_reply_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;
typedef  int /*<<< orphan*/  xcb_atom_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int /*<<< orphan*/  window; } ;
typedef  TYPE_1__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*) ; 
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ *) ; 
 TYPE_1__* con_by_window_id (int /*<<< orphan*/ ) ; 
 TYPE_1__* con_inside_floating (TYPE_1__*) ; 
 int /*<<< orphan*/  floating_check_size (TYPE_1__*,int) ; 
 int /*<<< orphan*/  tree_render () ; 
 int window_update_normal_hints (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool handle_normal_hints(void *data, xcb_connection_t *conn, uint8_t state, xcb_window_t window,
                                xcb_atom_t name, xcb_get_property_reply_t *reply) {
    Con *con = con_by_window_id(window);
    if (con == NULL) {
        DLOG("Received WM_NORMAL_HINTS for unknown client\n");
        return false;
    }

    bool changed = window_update_normal_hints(con->window, reply, NULL);

    if (changed) {
        Con *floating = con_inside_floating(con);
        if (floating) {
            floating_check_size(con, false);
            tree_render();
        }
    }

    FREE(reply);
    return true;
}