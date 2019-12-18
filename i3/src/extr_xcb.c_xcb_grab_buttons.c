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
typedef  int /*<<< orphan*/  xcb_window_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  XCB_BUTTON_MASK_ANY ; 
 int /*<<< orphan*/  XCB_EVENT_MASK_BUTTON_PRESS ; 
 int /*<<< orphan*/  XCB_GRAB_MODE_ASYNC ; 
 int /*<<< orphan*/  XCB_GRAB_MODE_SYNC ; 
 int /*<<< orphan*/  XCB_NONE ; 
 int /*<<< orphan*/  root ; 
 int /*<<< orphan*/  xcb_grab_button (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void xcb_grab_buttons(xcb_connection_t *conn, xcb_window_t window, int *buttons) {
    int i = 0;
    while (buttons[i] > 0) {
        xcb_grab_button(conn, false, window, XCB_EVENT_MASK_BUTTON_PRESS, XCB_GRAB_MODE_SYNC,
                        XCB_GRAB_MODE_ASYNC, root, XCB_NONE, buttons[i], XCB_BUTTON_MASK_ANY);

        i++;
    }
}