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
typedef  int uint32_t ;

/* Variables and functions */
 int JZ_CORESTS_MIRQ0P ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PCPU_GET (int /*<<< orphan*/ ) ; 
 int cpuid ; 
 int mips_rd_xburst_mbox0 () ; 
 int mips_rd_xburst_mbox1 () ; 
 int /*<<< orphan*/  mips_wr_xburst_core_sts (int) ; 

void
platform_ipi_clear(void)
{
	int cpuid = PCPU_GET(cpuid);
	uint32_t action;

	action = (cpuid == 0) ? mips_rd_xburst_mbox0() : mips_rd_xburst_mbox1();
	KASSERT(action == 1, ("CPU %d: unexpected IPIs: %#x", cpuid, action));
	mips_wr_xburst_core_sts(~(JZ_CORESTS_MIRQ0P << cpuid));
}