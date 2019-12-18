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
struct mce_bank {int /*<<< orphan*/  ctl; scalar_t__ init; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ctl ) (int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  cmci_reenable () ; 
 int /*<<< orphan*/  cpu_info ; 
 int /*<<< orphan*/  cpuhp_tasks_frozen ; 
 int /*<<< orphan*/  mce_available (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mce_banks_array ; 
 int /*<<< orphan*/  mce_num_banks ; 
 TYPE_1__ msr_ops ; 
 int /*<<< orphan*/  raw_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int) ; 
 struct mce_bank* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mce_reenable_cpu(void)
{
	struct mce_bank *mce_banks = this_cpu_ptr(mce_banks_array);
	int i;

	if (!mce_available(raw_cpu_ptr(&cpu_info)))
		return;

	if (!cpuhp_tasks_frozen)
		cmci_reenable();
	for (i = 0; i < this_cpu_read(mce_num_banks); i++) {
		struct mce_bank *b = &mce_banks[i];

		if (b->init)
			wrmsrl(msr_ops.ctl(i), b->ctl);
	}
}