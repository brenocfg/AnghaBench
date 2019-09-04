#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ visible; } ;
typedef  TYPE_2__ Window ;
struct TYPE_11__ {TYPE_1__* callback_os_window; } ;
struct TYPE_9__ {double mouse_x; double mouse_y; } ;
typedef  int /*<<< orphan*/  OSWindow ;

/* Variables and functions */
 TYPE_7__ global_state ; 
 double window_bottom (TYPE_2__*,int /*<<< orphan*/ *) ; 
 double window_left (TYPE_2__*,int /*<<< orphan*/ *) ; 
 double window_right (TYPE_2__*,int /*<<< orphan*/ *) ; 
 double window_top (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool
contains_mouse(Window *w, OSWindow *os_window) {
    double x = global_state.callback_os_window->mouse_x, y = global_state.callback_os_window->mouse_y;
    return (w->visible && window_left(w, os_window) <= x && x <= window_right(w, os_window) && window_top(w, os_window) <= y && y <= window_bottom(w, os_window));
}