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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  DCRN_405_CPC0_CR0 ; 
 int /*<<< orphan*/  DCRN_405_CPC0_CR1 ; 
 int /*<<< orphan*/  DCRN_405_CPC0_PSR ; 
 int /*<<< orphan*/  DCRN_CPC0_PLLMR ; 
 int /*<<< orphan*/  dt_fixup_clock (char*,int) ; 
 int /*<<< orphan*/  dt_fixup_cpu_clocks (int,int,int /*<<< orphan*/ ) ; 
 int mfdcr (int /*<<< orphan*/ ) ; 
 int mfpvr () ; 
 int /*<<< orphan*/  mtdcr (int /*<<< orphan*/ ,int) ; 

void ibm405gp_fixup_clocks(unsigned int sys_clk, unsigned int ser_clk)
{
	u32 pllmr = mfdcr(DCRN_CPC0_PLLMR);
	u32 cpc0_cr0 = mfdcr(DCRN_405_CPC0_CR0);
	u32 cpc0_cr1 = mfdcr(DCRN_405_CPC0_CR1);
	u32 psr = mfdcr(DCRN_405_CPC0_PSR);
	u32 cpu, plb, opb, ebc, tb, uart0, uart1, m;
	u32 fwdv, fwdvb, fbdv, cbdv, opdv, epdv, ppdv, udiv;

	fwdv = (8 - ((pllmr & 0xe0000000) >> 29));
	fbdv = (pllmr & 0x1e000000) >> 25;
	if (fbdv == 0)
		fbdv = 16;
	cbdv = ((pllmr & 0x00060000) >> 17) + 1; /* CPU:PLB */
	opdv = ((pllmr & 0x00018000) >> 15) + 1; /* PLB:OPB */
	ppdv = ((pllmr & 0x00006000) >> 13) + 1; /* PLB:PCI */
	epdv = ((pllmr & 0x00001800) >> 11) + 2; /* PLB:EBC */
	udiv = ((cpc0_cr0 & 0x3e) >> 1) + 1;

	/* check for 405GPr */
	if ((mfpvr() & 0xfffffff0) == (0x50910951 & 0xfffffff0)) {
		fwdvb = 8 - (pllmr & 0x00000007);
		if (!(psr & 0x00001000)) /* PCI async mode enable == 0 */
			if (psr & 0x00000020) /* New mode enable */
				m = fwdvb * 2 * ppdv;
			else
				m = fwdvb * cbdv * ppdv;
		else if (psr & 0x00000020) /* New mode enable */
			if (psr & 0x00000800) /* PerClk synch mode */
				m = fwdvb * 2 * epdv;
			else
				m = fbdv * fwdv;
		else if (epdv == fbdv)
			m = fbdv * cbdv * epdv;
		else
			m = fbdv * fwdvb * cbdv;

		cpu = sys_clk * m / fwdv;
		plb = sys_clk * m / (fwdvb * cbdv);
	} else {
		m = fwdv * fbdv * cbdv;
		cpu = sys_clk * m / fwdv;
		plb = cpu / cbdv;
	}
	opb = plb / opdv;
	ebc = plb / epdv;

	if (cpc0_cr0 & 0x80)
		/* uart0 uses the external clock */
		uart0 = ser_clk;
	else
		uart0 = cpu / udiv;

	if (cpc0_cr0 & 0x40)
		/* uart1 uses the external clock */
		uart1 = ser_clk;
	else
		uart1 = cpu / udiv;

	/* setup the timebase clock to tick at the cpu frequency */
	cpc0_cr1 = cpc0_cr1 & ~0x00800000;
	mtdcr(DCRN_405_CPC0_CR1, cpc0_cr1);
	tb = cpu;

	dt_fixup_cpu_clocks(cpu, tb, 0);
	dt_fixup_clock("/plb", plb);
	dt_fixup_clock("/plb/opb", opb);
	dt_fixup_clock("/plb/ebc", ebc);
	dt_fixup_clock("/plb/opb/serial@ef600300", uart0);
	dt_fixup_clock("/plb/opb/serial@ef600400", uart1);
}