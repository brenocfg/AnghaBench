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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_IA32_TSX_CTRL ; 
 int /*<<< orphan*/  TSX_CTRL_CPUID_CLEAR ; 
 int /*<<< orphan*/  TSX_CTRL_RTM_DISABLE ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void tsx_disable(void)
{
	u64 tsx;

	rdmsrl(MSR_IA32_TSX_CTRL, tsx);

	/* Force all transactions to immediately abort */
	tsx |= TSX_CTRL_RTM_DISABLE;

	/*
	 * Ensure TSX support is not enumerated in CPUID.
	 * This is visible to userspace and will ensure they
	 * do not waste resources trying TSX transactions that
	 * will always abort.
	 */
	tsx |= TSX_CTRL_CPUID_CLEAR;

	wrmsrl(MSR_IA32_TSX_CTRL, tsx);
}