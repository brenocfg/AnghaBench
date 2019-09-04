#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  id_type ;
typedef  int /*<<< orphan*/  Window ;
struct TYPE_2__ {int /*<<< orphan*/ * windows; } ;

/* Variables and functions */
 int /*<<< orphan*/  END_WITH_TAB ; 
 int /*<<< orphan*/  WITH_TAB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* tab ; 

__attribute__((used)) static inline void
swap_windows(id_type os_window_id, id_type tab_id, unsigned int a, unsigned int b) {
    WITH_TAB(os_window_id, tab_id);
    Window w = tab->windows[b];
    tab->windows[b] = tab->windows[a];
    tab->windows[a] = w;
    END_WITH_TAB;
}