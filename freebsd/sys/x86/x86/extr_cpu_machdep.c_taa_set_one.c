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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int IA32_TSX_CTRL_RTM_DISABLE ; 
 int IA32_TSX_CTRL_TSX_CPUID_CLEAR ; 
 int /*<<< orphan*/  MSR_IA32_TSX_CTRL ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
taa_set_one(bool enable)
{
	uint64_t v;

	v = rdmsr(MSR_IA32_TSX_CTRL);
	if (enable)
		v |= (uint64_t)(IA32_TSX_CTRL_RTM_DISABLE |
		    IA32_TSX_CTRL_TSX_CPUID_CLEAR);
	else
		v &= ~(uint64_t)(IA32_TSX_CTRL_RTM_DISABLE |
		    IA32_TSX_CTRL_TSX_CPUID_CLEAR);

	wrmsr(MSR_IA32_TSX_CTRL, v);
}