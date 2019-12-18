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
typedef  int /*<<< orphan*/  xcb_get_property_reply_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;
typedef  int /*<<< orphan*/  xcb_atom_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  window; } ;
typedef  TYPE_1__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*) ; 
 TYPE_1__* con_by_window_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  con_set_urgency (TYPE_1__*,int) ; 
 int /*<<< orphan*/  tree_render () ; 
 int /*<<< orphan*/  window_update_hints (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * xcb_get_property_reply (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_icccm_get_wm_hints (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool handle_hints(void *data, xcb_connection_t *conn, uint8_t state, xcb_window_t window,
                         xcb_atom_t name, xcb_get_property_reply_t *reply) {
    Con *con = con_by_window_id(window);
    if (con == NULL) {
        DLOG("Received WM_HINTS for unknown client\n");
        return false;
    }

    bool urgency_hint;
    if (reply == NULL)
        reply = xcb_get_property_reply(conn, xcb_icccm_get_wm_hints(conn, window), NULL);
    window_update_hints(con->window, reply, &urgency_hint);
    con_set_urgency(con, urgency_hint);
    tree_render();

    return true;
}