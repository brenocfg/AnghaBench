#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_window_t ;
typedef  int /*<<< orphan*/  xcb_get_property_reply_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;
typedef  int /*<<< orphan*/  xcb_atom_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_9__ {int /*<<< orphan*/ * name; } ;
struct TYPE_8__ {TYPE_2__* window; } ;
typedef  TYPE_1__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (char*) ; 
 TYPE_1__* con_by_window_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  croot ; 
 int /*<<< orphan*/  i3string_as_utf8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipc_send_window_event (char*,TYPE_1__*) ; 
 TYPE_1__* remanage_window (TYPE_1__*) ; 
 char* sstrdup (int /*<<< orphan*/ ) ; 
 scalar_t__ window_name_changed (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  window_update_name (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x_push_changes (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool handle_windowname_change(void *data, xcb_connection_t *conn, uint8_t state,
                                     xcb_window_t window, xcb_atom_t atom, xcb_get_property_reply_t *prop) {
    Con *con;
    if ((con = con_by_window_id(window)) == NULL || con->window == NULL)
        return false;

    char *old_name = (con->window->name != NULL ? sstrdup(i3string_as_utf8(con->window->name)) : NULL);

    window_update_name(con->window, prop);

    con = remanage_window(con);

    x_push_changes(croot);

    if (window_name_changed(con->window, old_name))
        ipc_send_window_event("title", con);

    FREE(old_name);

    return true;
}