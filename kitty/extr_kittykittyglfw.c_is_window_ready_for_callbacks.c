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
struct TYPE_4__ {scalar_t__ num_windows; } ;
typedef  TYPE_1__ Tab ;
struct TYPE_6__ {TYPE_2__* callback_os_window; } ;
struct TYPE_5__ {scalar_t__ num_tabs; int active_tab; TYPE_1__* tabs; } ;
typedef  TYPE_2__ OSWindow ;

/* Variables and functions */
 TYPE_3__ global_state ; 

__attribute__((used)) static inline bool
is_window_ready_for_callbacks() {
    OSWindow *w = global_state.callback_os_window;
    if (w->num_tabs == 0) return false;
    Tab *t = w->tabs + w->active_tab;
    if (t->num_windows == 0) return false;
    return true;
}