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
struct TYPE_6__ {int format; } ;
typedef  TYPE_1__ xcb_get_property_reply_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;
typedef  scalar_t__ xcb_atom_t ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  XCB_ATOM_ATOM ; 
 int /*<<< orphan*/  XCB_GET_PROPERTY_TYPE_ANY ; 
 int /*<<< orphan*/  XCB_PROP_MODE_REPLACE ; 
 int /*<<< orphan*/  xcb_change_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int,scalar_t__*) ; 
 int /*<<< orphan*/  xcb_get_property (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* xcb_get_property_reply (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__* xcb_get_property_value (TYPE_1__*) ; 
 int xcb_get_property_value_length (TYPE_1__*) ; 
 int /*<<< orphan*/  xcb_grab_server (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_ungrab_server (int /*<<< orphan*/ *) ; 

void xcb_remove_property_atom(xcb_connection_t *conn, xcb_window_t window, xcb_atom_t property, xcb_atom_t atom) {
    xcb_grab_server(conn);

    xcb_get_property_reply_t *reply =
        xcb_get_property_reply(conn,
                               xcb_get_property(conn, false, window, property, XCB_GET_PROPERTY_TYPE_ANY, 0, 4096), NULL);
    if (reply == NULL || xcb_get_property_value_length(reply) == 0)
        goto release_grab;
    xcb_atom_t *atoms = xcb_get_property_value(reply);
    if (atoms == NULL) {
        goto release_grab;
    }

    {
        int num = 0;
        const int current_size = xcb_get_property_value_length(reply) / (reply->format / 8);
        xcb_atom_t values[current_size];
        for (int i = 0; i < current_size; i++) {
            if (atoms[i] != atom)
                values[num++] = atoms[i];
        }

        xcb_change_property(conn, XCB_PROP_MODE_REPLACE, window, property, XCB_ATOM_ATOM, 32, num, values);
    }

release_grab:
    FREE(reply);
    xcb_ungrab_server(conn);
}