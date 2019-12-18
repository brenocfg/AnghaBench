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

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,int) ; 
 int /*<<< orphan*/  ev_feed_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_prepare_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_prepare_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  main_loop ; 
 int /*<<< orphan*/  xcb_prepare ; 

void main_set_x11_cb(bool enable) {
    DLOG("Setting main X11 callback to enabled=%d\n", enable);
    if (enable) {
        ev_prepare_start(main_loop, xcb_prepare);
        /* Trigger the watcher explicitly to handle all remaining X11 events.
         * drag_pointer()’s event handler exits in the middle of the loop. */
        ev_feed_event(main_loop, xcb_prepare, 0);
    } else {
        ev_prepare_stop(main_loop, xcb_prepare);
    }
}