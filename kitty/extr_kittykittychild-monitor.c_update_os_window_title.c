#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Window ;
struct TYPE_5__ {int active_window; int /*<<< orphan*/ * windows; scalar_t__ num_windows; } ;
typedef  TYPE_1__ Tab ;
struct TYPE_6__ {int active_tab; TYPE_1__* tabs; } ;
typedef  TYPE_2__ OSWindow ;

/* Variables and functions */
 int /*<<< orphan*/  update_window_title (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static inline void
update_os_window_title(OSWindow *os_window) {
    Tab *tab = os_window->tabs + os_window->active_tab;
    if (tab->num_windows) {
        Window *w = tab->windows + tab->active_window;
        update_window_title(w, os_window);
    }
}