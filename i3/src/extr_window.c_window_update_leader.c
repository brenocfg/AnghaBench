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
struct TYPE_3__ {int /*<<< orphan*/  leader; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ i3Window ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XCB_NONE ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xcb_get_property_value (int /*<<< orphan*/ *) ; 
 scalar_t__ xcb_get_property_value_length (int /*<<< orphan*/ *) ; 

void window_update_leader(i3Window *win, xcb_get_property_reply_t *prop) {
    if (prop == NULL || xcb_get_property_value_length(prop) == 0) {
        DLOG("CLIENT_LEADER not set on window 0x%08x.\n", win->id);
        win->leader = XCB_NONE;
        FREE(prop);
        return;
    }

    xcb_window_t *leader = xcb_get_property_value(prop);
    if (leader == NULL) {
        free(prop);
        return;
    }

    DLOG("Client leader changed to %08x\n", *leader);

    win->leader = *leader;

    free(prop);
}