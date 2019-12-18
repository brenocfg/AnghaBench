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
 int /*<<< orphan*/  AR5315_MEM_CFG_COL_WIDTH ; 
 int /*<<< orphan*/  AR5315_MEM_CFG_DATA_WIDTH ; 
 int /*<<< orphan*/  AR5315_MEM_CFG_ROW_WIDTH ; 
 scalar_t__ AR5315_SDRAMCTL_BASE ; 
 scalar_t__ AR5315_SDRAMCTL_MEM_CFG ; 
 int ATH_READ_REG (scalar_t__) ; 
 int __SHIFTOUT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int,int) ; 
 int realmem ; 

__attribute__((used)) static void
ar5315_chip_detect_mem_size(void)
{
	uint32_t	memsize = 0;
	uint32_t	memcfg, cw, rw, dw;

	/*
	 * Determine the memory size.  We query the board info.
	 */
	memcfg = ATH_READ_REG(AR5315_SDRAMCTL_BASE + AR5315_SDRAMCTL_MEM_CFG);
	cw = __SHIFTOUT(memcfg, AR5315_MEM_CFG_COL_WIDTH);
	cw += 1;
	rw = __SHIFTOUT(memcfg, AR5315_MEM_CFG_ROW_WIDTH);
	rw += 1;

	/* XXX: according to redboot, this could be wrong if DDR SDRAM */
	dw = __SHIFTOUT(memcfg, AR5315_MEM_CFG_DATA_WIDTH);
	dw += 1;
	dw *= 8;	/* bits */

	/* not too sure about this math, but it _seems_ to add up */
	memsize = (1 << cw) * (1 << rw) * dw;
#if 0
	printf("SDRAM_MEM_CFG =%x, cw=%d rw=%d dw=%d xmemsize=%d\n", memcfg,
	    cw, rw, dw, memsize);
#endif
	realmem = memsize;
}