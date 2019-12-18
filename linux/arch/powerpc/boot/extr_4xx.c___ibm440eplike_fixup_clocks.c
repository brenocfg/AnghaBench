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
 int CPR0_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DCRN_CPR0_OPBD ; 
 int /*<<< orphan*/  DCRN_CPR0_PERD ; 
 int /*<<< orphan*/  DCRN_CPR0_PLLC ; 
 int /*<<< orphan*/  DCRN_CPR0_PLLD ; 
 int /*<<< orphan*/  DCRN_CPR0_PRIMAD ; 
 int /*<<< orphan*/  DCRN_CPR0_PRIMBD ; 
 int /*<<< orphan*/  SPRN_CCR1 ; 
 int __fix_zero (int,int) ; 
 int /*<<< orphan*/  dt_fixup_clock (char*,int) ; 
 int /*<<< orphan*/  dt_fixup_cpu_clocks (int,int,int /*<<< orphan*/ ) ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static unsigned int __ibm440eplike_fixup_clocks(unsigned int sys_clk,
						unsigned int tmr_clk,
						int per_clk_from_opb)
{
	/* PLL config */
	u32 pllc  = CPR0_READ(DCRN_CPR0_PLLC);
	u32 plld  = CPR0_READ(DCRN_CPR0_PLLD);

	/* Dividers */
	u32 fbdv   = __fix_zero((plld >> 24) & 0x1f, 32);
	u32 fwdva  = __fix_zero((plld >> 16) & 0xf, 16);
	u32 fwdvb  = __fix_zero((plld >> 8) & 7, 8);
	u32 lfbdv  = __fix_zero(plld & 0x3f, 64);
	u32 pradv0 = __fix_zero((CPR0_READ(DCRN_CPR0_PRIMAD) >> 24) & 7, 8);
	u32 prbdv0 = __fix_zero((CPR0_READ(DCRN_CPR0_PRIMBD) >> 24) & 7, 8);
	u32 opbdv0 = __fix_zero((CPR0_READ(DCRN_CPR0_OPBD) >> 24) & 3, 4);
	u32 perdv0 = __fix_zero((CPR0_READ(DCRN_CPR0_PERD) >> 24) & 3, 4);

	/* Input clocks for primary dividers */
	u32 clk_a, clk_b;

	/* Resulting clocks */
	u32 cpu, plb, opb, ebc, vco;

	/* Timebase */
	u32 ccr1, tb = tmr_clk;

	if (pllc & 0x40000000) {
		u32 m;

		/* Feedback path */
		switch ((pllc >> 24) & 7) {
		case 0:
			/* PLLOUTx */
			m = ((pllc & 0x20000000) ? fwdvb : fwdva) * lfbdv;
			break;
		case 1:
			/* CPU */
			m = fwdva * pradv0;
			break;
		case 5:
			/* PERClk */
			m = fwdvb * prbdv0 * opbdv0 * perdv0;
			break;
		default:
			printf("WARNING ! Invalid PLL feedback source !\n");
			goto bypass;
		}
		m *= fbdv;
		vco = sys_clk * m;
		clk_a = vco / fwdva;
		clk_b = vco / fwdvb;
	} else {
bypass:
		/* Bypass system PLL */
		vco = 0;
		clk_a = clk_b = sys_clk;
	}

	cpu = clk_a / pradv0;
	plb = clk_b / prbdv0;
	opb = plb / opbdv0;
	ebc = (per_clk_from_opb ? opb : plb) / perdv0;

	/* Figure out timebase.  Either CPU or default TmrClk */
	ccr1 = mfspr(SPRN_CCR1);

	/* If passed a 0 tmr_clk, force CPU clock */
	if (tb == 0) {
		ccr1 &= ~0x80u;
		mtspr(SPRN_CCR1, ccr1);
	}
	if ((ccr1 & 0x0080) == 0)
		tb = cpu;

	dt_fixup_cpu_clocks(cpu, tb, 0);
	dt_fixup_clock("/plb", plb);
	dt_fixup_clock("/plb/opb", opb);
	dt_fixup_clock("/plb/opb/ebc", ebc);

	return plb;
}