#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t id_type ;
struct TYPE_5__ {size_t num_windows; TYPE_1__* windows; } ;
typedef  TYPE_2__ Tab ;
struct TYPE_4__ {size_t id; } ;

/* Variables and functions */

__attribute__((used)) static inline bool
fix_window_idx(Tab *tab, id_type window_id, unsigned int *window_idx) {
    for (id_type fix = 0; fix < tab->num_windows; fix++) {
        if (tab->windows[fix].id == window_id) { *window_idx = fix; return true; }
    }
    return false;
}