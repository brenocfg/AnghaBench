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
struct sort_level {int dummy; } ;

/* Variables and functions */
 struct sort_level* pop_ls_st () ; 
 int /*<<< orphan*/  run_sort_level_next (struct sort_level*) ; 

__attribute__((used)) static void
run_sort_cycle_st(void)
{
	struct sort_level *slc;

	for (;;) {
		slc = pop_ls_st();
		if (slc == NULL) {
			break;
		}
		run_sort_level_next(slc);
	}
}