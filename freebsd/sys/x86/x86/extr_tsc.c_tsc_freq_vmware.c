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
typedef  int uint64_t ;
typedef  int u_int ;

/* Variables and functions */
 int UINT_MAX ; 
 int /*<<< orphan*/  VMW_HVCMD_GETHZ ; 
 int /*<<< orphan*/  do_cpuid (int,int*) ; 
 int hv_high ; 
 int tsc_freq ; 
 int tsc_is_invariant ; 
 int /*<<< orphan*/  vmware_hvcall (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void
tsc_freq_vmware(void)
{
	u_int regs[4];

	if (hv_high >= 0x40000010) {
		do_cpuid(0x40000010, regs);
		tsc_freq = regs[0] * 1000;
	} else {
		vmware_hvcall(VMW_HVCMD_GETHZ, regs);
		if (regs[1] != UINT_MAX)
			tsc_freq = regs[0] | ((uint64_t)regs[1] << 32);
	}
	tsc_is_invariant = 1;
}