#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  baud ;
struct TYPE_2__ {int /*<<< orphan*/  bi_plb_busfreq; int /*<<< orphan*/  bi_intfreq; int /*<<< orphan*/  bi_procfreq; } ;

/* Variables and functions */
 unsigned long CPR0_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DCRN_CPR0_PLLC ; 
 int /*<<< orphan*/  DCRN_CPR0_PLLD ; 
 int /*<<< orphan*/  DCRN_CPR0_PRIMAD ; 
 unsigned long PLLC_SRC_MASK ; 
 unsigned long PLLD_FBDV_MASK ; 
 unsigned long PLLD_FWDVA_MASK ; 
 unsigned long PLLD_FWDVB_MASK ; 
 unsigned long PRIMAD_EBCDV_MASK ; 
 unsigned long PRIMAD_OPBDV_MASK ; 
 unsigned long PRIMAD_PLBDV_MASK ; 
 TYPE_1__ bd ; 
 int /*<<< orphan*/  dt_fixup_clock (char*,unsigned long) ; 
 int /*<<< orphan*/  dt_fixup_cpu_clocks (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 void* find_node_by_alias (char*) ; 
 int getprop (void*,char*,unsigned long*,int) ; 
 int in_8 (unsigned char*) ; 

__attribute__((used)) static void get_clocks(void)
{
	unsigned long sysclk, cpr_plld, cpr_pllc, cpr_primad, plloutb, i;
	unsigned long pllFwdDiv, pllFwdDivB, pllFbkDiv, pllPlbDiv, pllExtBusDiv;
	unsigned long pllOpbDiv, freqEBC, freqUART, freqOPB;
	unsigned long div;		/* total divisor udiv * bdiv */
	unsigned long umin;		/* minimum udiv	*/
	unsigned short diff;		/* smallest diff */
	unsigned long udiv;		/* best udiv */
	unsigned short idiff;		/* current diff */
	unsigned short ibdiv;		/* current bdiv */
	unsigned long est;		/* current estimate */
	unsigned long baud;
	void *np;

	/* read the sysclk value from the CPLD */
	sysclk = (in_8((unsigned char *)0x80000000) == 0xc) ? 66666666 : 33333000;

	/*
	 * Read PLL Mode registers
	 */
	cpr_plld = CPR0_READ(DCRN_CPR0_PLLD);
	cpr_pllc = CPR0_READ(DCRN_CPR0_PLLC);

	/*
	 * Determine forward divider A
	 */
	pllFwdDiv = ((cpr_plld & PLLD_FWDVA_MASK) >> 16);

	/*
	 * Determine forward divider B
	 */
	pllFwdDivB = ((cpr_plld & PLLD_FWDVB_MASK) >> 8);
	if (pllFwdDivB == 0)
		pllFwdDivB = 8;

	/*
	 * Determine FBK_DIV.
	 */
	pllFbkDiv = ((cpr_plld & PLLD_FBDV_MASK) >> 24);
	if (pllFbkDiv == 0)
		pllFbkDiv = 256;

	/*
	 * Read CPR_PRIMAD register
	 */
	cpr_primad = CPR0_READ(DCRN_CPR0_PRIMAD);

	/*
	 * Determine PLB_DIV.
	 */
	pllPlbDiv = ((cpr_primad & PRIMAD_PLBDV_MASK) >> 16);
	if (pllPlbDiv == 0)
		pllPlbDiv = 16;

	/*
	 * Determine EXTBUS_DIV.
	 */
	pllExtBusDiv = (cpr_primad & PRIMAD_EBCDV_MASK);
	if (pllExtBusDiv == 0)
		pllExtBusDiv = 16;

	/*
	 * Determine OPB_DIV.
	 */
	pllOpbDiv = ((cpr_primad & PRIMAD_OPBDV_MASK) >> 8);
	if (pllOpbDiv == 0)
		pllOpbDiv = 16;

	/* There is a bug in U-Boot that prevents us from using
	 * bd.bi_opbfreq because U-Boot doesn't populate it for
	 * 405EZ.  We get to calculate it, yay!
	 */
	freqOPB = (sysclk *pllFbkDiv) /pllOpbDiv;

	freqEBC = (sysclk * pllFbkDiv) / pllExtBusDiv;

	plloutb = ((sysclk * ((cpr_pllc & PLLC_SRC_MASK) ?
					   pllFwdDivB : pllFwdDiv) *
		    pllFbkDiv) / pllFwdDivB);

	np = find_node_by_alias("serial0");
	if (getprop(np, "current-speed", &baud, sizeof(baud)) != sizeof(baud))
		fatal("no current-speed property\n\r");

	udiv = 256;			/* Assume lowest possible serial clk */
	div = plloutb / (16 * baud); /* total divisor */
	umin = (plloutb / freqOPB) << 1;	/* 2 x OPB divisor */
	diff = 256;			/* highest possible */

	/* i is the test udiv value -- start with the largest
	 * possible (256) to minimize serial clock and constrain
	 * search to umin.
	 */
	for (i = 256; i > umin; i--) {
		ibdiv = div / i;
		est = i * ibdiv;
		idiff = (est > div) ? (est-div) : (div-est);
		if (idiff == 0) {
			udiv = i;
			break;      /* can't do better */
		} else if (idiff < diff) {
			udiv = i;       /* best so far */
			diff = idiff;   /* update lowest diff*/
		}
	}
	freqUART = plloutb / udiv;

	dt_fixup_cpu_clocks(bd.bi_procfreq, bd.bi_intfreq, bd.bi_plb_busfreq);
	dt_fixup_clock("/plb/ebc", freqEBC);
	dt_fixup_clock("/plb/opb", freqOPB);
	dt_fixup_clock("/plb/opb/serial@ef600300", freqUART);
	dt_fixup_clock("/plb/opb/serial@ef600400", freqUART);
}