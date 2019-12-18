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
typedef  int /*<<< orphan*/  xcb_get_property_reply_t ;
typedef  scalar_t__ xcb_atom_t ;
struct TYPE_4__ {scalar_t__ window_type; } ;
typedef  TYPE_1__ i3Window ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*) ; 
 int /*<<< orphan*/  LOG (char*,scalar_t__) ; 
 scalar_t__ XCB_NONE ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  run_assignments (TYPE_1__*) ; 
 scalar_t__ xcb_get_preferred_window_type (int /*<<< orphan*/ *) ; 

void window_update_type(i3Window *window, xcb_get_property_reply_t *reply) {
    xcb_atom_t new_type = xcb_get_preferred_window_type(reply);
    free(reply);
    if (new_type == XCB_NONE) {
        DLOG("cannot read _NET_WM_WINDOW_TYPE from window.\n");
        return;
    }

    window->window_type = new_type;
    LOG("_NET_WM_WINDOW_TYPE changed to %i.\n", window->window_type);

    run_assignments(window);
}