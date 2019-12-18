#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; int /*<<< orphan*/  input; } ;
typedef  TYPE_1__ xcb_icccm_wm_hints_t ;
typedef  int /*<<< orphan*/  xcb_get_property_reply_t ;
struct TYPE_7__ {int doesnt_accept_focus; } ;
typedef  TYPE_2__ i3Window ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*) ; 
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG (char*,int /*<<< orphan*/ ) ; 
 int XCB_ICCCM_WM_HINT_INPUT ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ xcb_get_property_value_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_icccm_get_wm_hints_from_reply (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ xcb_icccm_wm_hints_get_urgency (TYPE_1__*) ; 

void window_update_hints(i3Window *win, xcb_get_property_reply_t *prop, bool *urgency_hint) {
    if (urgency_hint != NULL)
        *urgency_hint = false;

    if (prop == NULL || xcb_get_property_value_length(prop) == 0) {
        DLOG("WM_HINTS not set.\n");
        FREE(prop);
        return;
    }

    xcb_icccm_wm_hints_t hints;

    if (!xcb_icccm_get_wm_hints_from_reply(&hints, prop)) {
        DLOG("Could not get WM_HINTS\n");
        free(prop);
        return;
    }

    if (hints.flags & XCB_ICCCM_WM_HINT_INPUT) {
        win->doesnt_accept_focus = !hints.input;
        LOG("WM_HINTS.input changed to \"%d\"\n", hints.input);
    }

    if (urgency_hint != NULL)
        *urgency_hint = (xcb_icccm_wm_hints_get_urgency(&hints) != 0);

    free(prop);
}