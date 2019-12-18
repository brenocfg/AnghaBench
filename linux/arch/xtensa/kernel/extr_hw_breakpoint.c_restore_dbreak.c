#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct perf_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIF_DB_DISABLED ; 
 int XCHAL_NUM_DBREAK ; 
 int /*<<< orphan*/  clear_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dbreak_regs (int,struct perf_event*) ; 
 struct perf_event** this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wp_on_reg ; 

void restore_dbreak(void)
{
	int i;

	for (i = 0; i < XCHAL_NUM_DBREAK; ++i) {
		struct perf_event *bp = this_cpu_ptr(wp_on_reg)[i];

		if (bp)
			set_dbreak_regs(i, bp);
	}
	clear_thread_flag(TIF_DB_DISABLED);
}