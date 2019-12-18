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
typedef  int u32 ;

/* Variables and functions */
 scalar_t__ AR7_REGS_GPIO ; 
 scalar_t__ KSEG1ADDR (scalar_t__) ; 
 int ar7_chip_rev () ; 
 int readl (void*) ; 

__attribute__((used)) static int tnetd7300_dsp_clock(void)
{
	u32 didr1, didr2;
	u8 rev = ar7_chip_rev();
	didr1 = readl((void *)KSEG1ADDR(AR7_REGS_GPIO + 0x18));
	didr2 = readl((void *)KSEG1ADDR(AR7_REGS_GPIO + 0x1c));
	if (didr2 & (1 << 23))
		return 0;
	if ((rev >= 0x23) && (rev != 0x57))
		return 250000000;
	if ((((didr2 & 0x1fff) << 10) | ((didr1 & 0xffc00000) >> 22))
	    > 4208000)
		return 250000000;
	return 0;
}