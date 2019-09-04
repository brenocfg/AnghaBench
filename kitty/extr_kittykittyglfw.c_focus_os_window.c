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
struct TYPE_3__ {scalar_t__ handle; } ;
typedef  TYPE_1__ OSWindow ;

/* Variables and functions */
 int /*<<< orphan*/  glfwFocusWindow (scalar_t__) ; 

void
focus_os_window(OSWindow *w, bool also_raise) {
    if (w->handle) {
#ifdef __APPLE__
        if (!also_raise) cocoa_focus_window(glfwGetCocoaWindow(w->handle));
        else glfwFocusWindow(w->handle);
#else
        (void)also_raise;
        glfwFocusWindow(w->handle);
#endif
    }
}