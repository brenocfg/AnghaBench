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
struct TYPE_2__ {int /*<<< orphan*/ * lbr_exclusive; scalar_t__ lbr_pt_coexist; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EBUSY ; 
 int /*<<< orphan*/  active_events ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmc_reserve_mutex ; 
 unsigned int x86_lbr_exclusive_pt ; 
 TYPE_1__ x86_pmu ; 

int x86_add_exclusive(unsigned int what)
{
	int i;

	/*
	 * When lbr_pt_coexist we allow PT to coexist with either LBR or BTS.
	 * LBR and BTS are still mutually exclusive.
	 */
	if (x86_pmu.lbr_pt_coexist && what == x86_lbr_exclusive_pt)
		return 0;

	if (!atomic_inc_not_zero(&x86_pmu.lbr_exclusive[what])) {
		mutex_lock(&pmc_reserve_mutex);
		for (i = 0; i < ARRAY_SIZE(x86_pmu.lbr_exclusive); i++) {
			if (i != what && atomic_read(&x86_pmu.lbr_exclusive[i]))
				goto fail_unlock;
		}
		atomic_inc(&x86_pmu.lbr_exclusive[what]);
		mutex_unlock(&pmc_reserve_mutex);
	}

	atomic_inc(&active_events);
	return 0;

fail_unlock:
	mutex_unlock(&pmc_reserve_mutex);
	return -EBUSY;
}