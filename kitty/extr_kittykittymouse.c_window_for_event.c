#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ screen; } ;
struct TYPE_10__ {TYPE_1__ render_data; } ;
typedef  TYPE_2__ Window ;
struct TYPE_11__ {unsigned int num_windows; TYPE_2__* windows; } ;
typedef  TYPE_3__ Tab ;
struct TYPE_13__ {TYPE_5__* callback_os_window; } ;
struct TYPE_12__ {scalar_t__ num_tabs; int active_tab; TYPE_3__* tabs; } ;
typedef  int /*<<< orphan*/  Region ;

/* Variables and functions */
 scalar_t__ contains_mouse (TYPE_2__*,TYPE_5__*) ; 
 TYPE_6__ global_state ; 
 int mouse_in_region (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_window_regions (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline Window*
window_for_event(unsigned int *window_idx, bool *in_tab_bar) {
    Region central, tab_bar;
    os_window_regions(global_state.callback_os_window, &central, &tab_bar);
    *in_tab_bar = mouse_in_region(&tab_bar);
    if (!*in_tab_bar && global_state.callback_os_window->num_tabs > 0) {
        Tab *t = global_state.callback_os_window->tabs + global_state.callback_os_window->active_tab;
        for (unsigned int i = 0; i < t->num_windows; i++) {
            if (contains_mouse(t->windows + i, global_state.callback_os_window) && t->windows[i].render_data.screen) {
                *window_idx = i; return t->windows + i;
            }
        }
    }
    return NULL;
}