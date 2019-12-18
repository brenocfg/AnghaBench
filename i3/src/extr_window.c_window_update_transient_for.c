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
struct TYPE_3__ {int /*<<< orphan*/  transient_for; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ i3Window ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XCB_NONE ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ xcb_get_property_value_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_icccm_get_wm_transient_for_from_reply (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void window_update_transient_for(i3Window *win, xcb_get_property_reply_t *prop) {
    if (prop == NULL || xcb_get_property_value_length(prop) == 0) {
        DLOG("TRANSIENT_FOR not set on window 0x%08x.\n", win->id);
        win->transient_for = XCB_NONE;
        FREE(prop);
        return;
    }

    xcb_window_t transient_for;
    if (!xcb_icccm_get_wm_transient_for_from_reply(&transient_for, prop)) {
        free(prop);
        return;
    }

    DLOG("Transient for changed to 0x%08x (window 0x%08x)\n", transient_for, win->id);

    win->transient_for = transient_for;

    free(prop);
}