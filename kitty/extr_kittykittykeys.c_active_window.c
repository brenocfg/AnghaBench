#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ screen; } ;
struct TYPE_9__ {TYPE_2__ render_data; } ;
typedef  TYPE_3__ Window ;
struct TYPE_10__ {int active_window; TYPE_3__* windows; } ;
typedef  TYPE_4__ Tab ;
struct TYPE_11__ {TYPE_1__* callback_os_window; } ;
struct TYPE_7__ {int active_tab; TYPE_4__* tabs; } ;

/* Variables and functions */
 TYPE_5__ global_state ; 

__attribute__((used)) static inline Window*
active_window() {
    Tab *t = global_state.callback_os_window->tabs + global_state.callback_os_window->active_tab;
    Window *w = t->windows + t->active_window;
    if (w->render_data.screen) return w;
    return NULL;
}