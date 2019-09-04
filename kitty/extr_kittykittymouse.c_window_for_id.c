#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ id_type ;
struct TYPE_7__ {scalar_t__ id; } ;
typedef  TYPE_2__ Window ;
struct TYPE_8__ {unsigned int num_windows; TYPE_2__* windows; } ;
typedef  TYPE_3__ Tab ;
struct TYPE_9__ {TYPE_1__* callback_os_window; } ;
struct TYPE_6__ {int active_tab; TYPE_3__* tabs; } ;

/* Variables and functions */
 TYPE_5__ global_state ; 

__attribute__((used)) static inline Window*
window_for_id(id_type window_id) {
    Tab *t = global_state.callback_os_window->tabs + global_state.callback_os_window->active_tab;
    for (unsigned int i = 0; i < t->num_windows; i++) {
        Window *w = t->windows + i;
        if (w->id == window_id) return w;
    }
    return NULL;
}