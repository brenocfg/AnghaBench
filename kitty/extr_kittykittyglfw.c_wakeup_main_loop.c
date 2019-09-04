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
 int /*<<< orphan*/  glfwPostEmptyEvent () ; 
 int /*<<< orphan*/  request_tick_callback () ; 

void
wakeup_main_loop() {
    request_tick_callback();
#ifndef __APPLE__
    // On Cocoa request_tick_callback() uses performSelectorOnMainLoop which
    // wakes up the main loop anyway
    glfwPostEmptyEvent();
#endif
}