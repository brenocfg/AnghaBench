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
typedef  int u8 ;
struct mce_bank {unsigned long long ctl; int init; } ;

/* Variables and functions */
 int /*<<< orphan*/  mce_banks_array ; 
 int /*<<< orphan*/  mce_num_banks ; 
 struct mce_bank* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int this_cpu_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __mcheck_cpu_mce_banks_init(void)
{
	struct mce_bank *mce_banks = this_cpu_ptr(mce_banks_array);
	u8 n_banks = this_cpu_read(mce_num_banks);
	int i;

	for (i = 0; i < n_banks; i++) {
		struct mce_bank *b = &mce_banks[i];

		/*
		 * Init them all, __mcheck_cpu_apply_quirks() is going to apply
		 * the required vendor quirks before
		 * __mcheck_cpu_init_clear_banks() does the final bank setup.
		 */
		b->ctl = -1ULL;
		b->init = 1;
	}
}