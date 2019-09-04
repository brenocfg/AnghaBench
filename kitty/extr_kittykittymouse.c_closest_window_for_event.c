#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Window ;
struct TYPE_4__ {unsigned int num_windows; int /*<<< orphan*/ * windows; } ;
typedef  TYPE_1__ Tab ;
struct TYPE_6__ {scalar_t__ num_tabs; int active_tab; TYPE_1__* tabs; } ;
struct TYPE_5__ {TYPE_3__* callback_os_window; } ;

/* Variables and functions */
 double UINT_MAX ; 
 double distance_to_window (int /*<<< orphan*/ *,TYPE_3__*) ; 
 TYPE_2__ global_state ; 

__attribute__((used)) static inline Window*
closest_window_for_event(unsigned int *window_idx) {
    Window *ans = NULL;
    double closest_distance = UINT_MAX;
    if (global_state.callback_os_window->num_tabs > 0) {
        Tab *t = global_state.callback_os_window->tabs + global_state.callback_os_window->active_tab;
        for (unsigned int i = 0; i < t->num_windows; i++) {
            Window *w = t->windows + i;
            double d = distance_to_window(w, global_state.callback_os_window);
            if (d < closest_distance) { ans = w; closest_distance = d; *window_idx = i; }
        }
    }
    return ans;
}