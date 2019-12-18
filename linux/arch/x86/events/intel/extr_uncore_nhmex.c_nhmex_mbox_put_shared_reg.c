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
struct intel_uncore_extra_reg {int /*<<< orphan*/  ref; } ;
struct intel_uncore_box {struct intel_uncore_extra_reg* shared_regs; } ;

/* Variables and functions */
 int EXTRA_REG_NHMEX_M_ZDP_CTL_FVC ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_sub (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nhmex_mbox_put_shared_reg(struct intel_uncore_box *box, int idx)
{
	struct intel_uncore_extra_reg *er;

	if (idx < EXTRA_REG_NHMEX_M_ZDP_CTL_FVC) {
		er = &box->shared_regs[idx];
		atomic_dec(&er->ref);
		return;
	}

	idx -= EXTRA_REG_NHMEX_M_ZDP_CTL_FVC;
	er = &box->shared_regs[EXTRA_REG_NHMEX_M_ZDP_CTL_FVC];
	atomic_sub(1 << (idx * 8), &er->ref);
}