#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_window_t ;
typedef  int /*<<< orphan*/  xcb_get_property_reply_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;
typedef  int /*<<< orphan*/  xcb_atom_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/ * window; } ;
typedef  TYPE_1__ Con ;

/* Variables and functions */
 TYPE_1__* con_by_window_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  window_update_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool handle_window_type(void *data, xcb_connection_t *conn, uint8_t state, xcb_window_t window,
                               xcb_atom_t atom, xcb_get_property_reply_t *reply) {
    Con *con;
    if ((con = con_by_window_id(window)) == NULL || con->window == NULL)
        return false;

    window_update_type(con->window, reply);
    return true;
}