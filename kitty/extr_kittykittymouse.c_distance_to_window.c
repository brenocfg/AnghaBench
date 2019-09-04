#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Window ;
struct TYPE_4__ {TYPE_1__* callback_os_window; } ;
struct TYPE_3__ {double mouse_x; double mouse_y; } ;
typedef  int /*<<< orphan*/  OSWindow ;

/* Variables and functions */
 TYPE_2__ global_state ; 
 double window_bottom (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 double window_left (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 double window_right (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 double window_top (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline double
distance_to_window(Window *w, OSWindow *os_window) {
    double x = global_state.callback_os_window->mouse_x, y = global_state.callback_os_window->mouse_y;
    double cx = (window_left(w, os_window) + window_right(w, os_window)) / 2.0;
    double cy = (window_top(w, os_window) + window_bottom(w, os_window)) / 2.0;
    return (x - cx) * (x - cx) + (y - cy) * (y - cy);
}