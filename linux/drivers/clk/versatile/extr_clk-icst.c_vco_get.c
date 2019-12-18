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
struct icst_vco {int v; int r; int s; } ;
struct clk_icst {scalar_t__ ctype; int /*<<< orphan*/  vcoreg_off; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 scalar_t__ ICST_INTEGRATOR_AP_CM ; 
 scalar_t__ ICST_INTEGRATOR_AP_PCI ; 
 scalar_t__ ICST_INTEGRATOR_AP_SYS ; 
 scalar_t__ ICST_INTEGRATOR_CP_CM_CORE ; 
 scalar_t__ ICST_INTEGRATOR_CP_CM_MEM ; 
 int INTEGRATOR_AP_CM_BITS ; 
 int INTEGRATOR_AP_PCI_25_33_MHZ ; 
 int INTEGRATOR_AP_SYS_BITS ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int vco_get(struct clk_icst *icst, struct icst_vco *vco)
{
	u32 val;
	int ret;

	ret = regmap_read(icst->map, icst->vcoreg_off, &val);
	if (ret)
		return ret;

	/*
	 * The Integrator/AP core clock can only access the low eight
	 * bits of the v PLL divider. Bit 8 is tied low and always zero,
	 * r is hardwired to 22 and output divider s is hardwired to 1
	 * (divide by 2) according to the document
	 * "Integrator CM926EJ-S, CM946E-S, CM966E-S, CM1026EJ-S and
	 * CM1136JF-S User Guide" ARM DUI 0138E, page 3-13 thru 3-14.
	 */
	if (icst->ctype == ICST_INTEGRATOR_AP_CM) {
		vco->v = val & INTEGRATOR_AP_CM_BITS;
		vco->r = 22;
		vco->s = 1;
		return 0;
	}

	/*
	 * The Integrator/AP system clock on the base board can only
	 * access the low eight bits of the v PLL divider. Bit 8 is tied low
	 * and always zero, r is hardwired to 46, and the output divider is
	 * hardwired to 3 (divide by 4) according to the document
	 * "Integrator AP ASIC Development Motherboard" ARM DUI 0098B,
	 * page 3-16.
	 */
	if (icst->ctype == ICST_INTEGRATOR_AP_SYS) {
		vco->v = val & INTEGRATOR_AP_SYS_BITS;
		vco->r = 46;
		vco->s = 3;
		return 0;
	}

	/*
	 * The Integrator/AP PCI clock is using an odd pattern to create
	 * the child clock, basically a single bit called DIVX/Y is used
	 * to select between two different hardwired values: setting the
	 * bit to 0 yields v = 17, r = 22 and OD = 1, whereas setting the
	 * bit to 1 yields v = 14, r = 14 and OD = 1 giving the frequencies
	 * 33 or 25 MHz respectively.
	 */
	if (icst->ctype == ICST_INTEGRATOR_AP_PCI) {
		bool divxy = !!(val & INTEGRATOR_AP_PCI_25_33_MHZ);

		vco->v = divxy ? 17 : 14;
		vco->r = divxy ? 22 : 14;
		vco->s = 1;
		return 0;
	}

	/*
	 * The Integrator/CP core clock can access the low eight bits
	 * of the v PLL divider. Bit 8 is tied low and always zero,
	 * r is hardwired to 22 and the output divider s is accessible
	 * in bits 8 thru 10 according to the document
	 * "Integrator/CM940T, CM920T, CM740T, and CM720T User Guide"
	 * ARM DUI 0157A, page 3-20 thru 3-23 and 4-10.
	 */
	if (icst->ctype == ICST_INTEGRATOR_CP_CM_CORE) {
		vco->v = val & 0xFF;
		vco->r = 22;
		vco->s = (val >> 8) & 7;
		return 0;
	}

	if (icst->ctype == ICST_INTEGRATOR_CP_CM_MEM) {
		vco->v = (val >> 12) & 0xFF;
		vco->r = 22;
		vco->s = (val >> 20) & 7;
		return 0;
	}

	vco->v = val & 0x1ff;
	vco->r = (val >> 9) & 0x7f;
	vco->s = (val >> 16) & 03;
	return 0;
}