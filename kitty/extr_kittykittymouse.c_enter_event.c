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

void
enter_event() {
#ifdef __APPLE__
    // On cocoa there is no way to configure the window manager to
    // focus windows on mouse enter, so we do it ourselves
    if (OPT(focus_follows_mouse) && !global_state.callback_os_window->is_focused) {
        focus_os_window(global_state.callback_os_window, false);
    }
#endif
}