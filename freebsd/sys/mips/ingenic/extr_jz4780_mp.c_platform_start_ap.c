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
 int EINVAL ; 
 int JZ4780_MAXCPU ; 
 int JZ_CORECTL_RPC0 ; 
 int JZ_CORECTL_SWRST0 ; 
 int JZ_REIM_ENTRY_MASK ; 
 int JZ_REIM_MIRQ0M ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MIPS_KSEG0_TO_PHYS (int /*<<< orphan*/ ) ; 
 int MIPS_PHYS_TO_KSEG1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jz4780_core_powerup () ; 
 int /*<<< orphan*/  jz4780_mpentry ; 
 int mips_rd_xburst_core_ctl () ; 
 int mips_rd_xburst_reim () ; 
 int /*<<< orphan*/  mips_wr_xburst_core_ctl (int) ; 
 int /*<<< orphan*/  mips_wr_xburst_reim (int) ; 

int
platform_start_ap(int cpuid)
{
	uint32_t reg, addr;

	if (cpuid >= JZ4780_MAXCPU)
		return (EINVAL);

	/* Figure out address of mpentry in KSEG1 */
	addr = MIPS_PHYS_TO_KSEG1(MIPS_KSEG0_TO_PHYS(jz4780_mpentry));
	KASSERT((addr & ~JZ_REIM_ENTRY_MASK) == 0,
	    ("Unaligned mpentry"));

	/* Configure core alternative entry point */
	reg = mips_rd_xburst_reim();
	reg &= ~JZ_REIM_ENTRY_MASK;
	reg |= addr & JZ_REIM_ENTRY_MASK;

	/* Allow this core to get IPIs from one being started */
	reg |= JZ_REIM_MIRQ0M;
	mips_wr_xburst_reim(reg);

	/* Force core into reset and enable use of alternate entry point */
	reg = mips_rd_xburst_core_ctl();
	reg |= (JZ_CORECTL_SWRST0 << cpuid) | (JZ_CORECTL_RPC0 << cpuid);
	mips_wr_xburst_core_ctl(reg);

	/* Power the core up */
	jz4780_core_powerup();

	/* Take the core out of reset */
	reg &= ~(JZ_CORECTL_SWRST0 << cpuid);
	mips_wr_xburst_core_ctl(reg);

	return (0);
}