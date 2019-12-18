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
typedef  int u64 ;
struct mce {int bank; int /*<<< orphan*/  extcpu; } ;

/* Variables and functions */
 int EINVAL ; 
 int MCG_BANKCNT_MASK ; 
 int /*<<< orphan*/  MSR_IA32_MCG_CAP ; 
 int /*<<< orphan*/  do_inject () ; 
 int /*<<< orphan*/  i_mce ; 
 int /*<<< orphan*/  pr_err (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdmsrl_on_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  setup_inj_struct (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int inj_bank_set(void *data, u64 val)
{
	struct mce *m = (struct mce *)data;
	u8 n_banks;
	u64 cap;

	/* Get bank count on target CPU so we can handle non-uniform values. */
	rdmsrl_on_cpu(m->extcpu, MSR_IA32_MCG_CAP, &cap);
	n_banks = cap & MCG_BANKCNT_MASK;

	if (val >= n_banks) {
		pr_err("MCA bank %llu non-existent on CPU%d\n", val, m->extcpu);
		return -EINVAL;
	}

	m->bank = val;
	do_inject();

	/* Reset injection struct */
	setup_inj_struct(&i_mce);

	return 0;
}