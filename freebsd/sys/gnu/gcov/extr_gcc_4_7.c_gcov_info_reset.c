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
struct gcov_info {unsigned int n_functions; TYPE_1__** functions; } ;
struct gcov_ctr_info {int num; int /*<<< orphan*/  values; } ;
typedef  int /*<<< orphan*/  gcov_type ;
struct TYPE_2__ {struct gcov_ctr_info* ctrs; } ;

/* Variables and functions */
 unsigned int GCOV_COUNTERS ; 
 int /*<<< orphan*/  counter_active (struct gcov_info*,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
gcov_info_reset(struct gcov_info *info)
{
	struct gcov_ctr_info *ci_ptr;
	unsigned int fi_idx;
	unsigned int ct_idx;

	for (fi_idx = 0; fi_idx < info->n_functions; fi_idx++) {
		ci_ptr = info->functions[fi_idx]->ctrs;

		for (ct_idx = 0; ct_idx < GCOV_COUNTERS; ct_idx++) {
			if (!counter_active(info, ct_idx))
				continue;

			memset(ci_ptr->values, 0,
					sizeof(gcov_type) * ci_ptr->num);
			ci_ptr++;
		}
	}
}