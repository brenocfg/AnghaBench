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
struct TYPE_2__ {size_t num_os_windows; int /*<<< orphan*/ * os_windows; } ;

/* Variables and functions */
 TYPE_1__ global_state ; 
 int /*<<< orphan*/  mark_os_window_for_close (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void
close_all_windows() {
    for (size_t w = 0; w < global_state.num_os_windows; w++) mark_os_window_for_close(&global_state.os_windows[w], true);
}