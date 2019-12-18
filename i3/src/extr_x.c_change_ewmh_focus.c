#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ xcb_window_t ;

/* Variables and functions */
 scalar_t__ XCB_WINDOW_NONE ; 
 int /*<<< orphan*/  ewmh_update_active_window (scalar_t__) ; 
 int /*<<< orphan*/  ewmh_update_focused (scalar_t__,int) ; 

__attribute__((used)) static void change_ewmh_focus(xcb_window_t new_focus, xcb_window_t old_focus) {
    if (new_focus == old_focus) {
        return;
    }

    ewmh_update_active_window(new_focus);

    if (new_focus != XCB_WINDOW_NONE) {
        ewmh_update_focused(new_focus, true);
    }

    if (old_focus != XCB_WINDOW_NONE) {
        ewmh_update_focused(old_focus, false);
    }
}