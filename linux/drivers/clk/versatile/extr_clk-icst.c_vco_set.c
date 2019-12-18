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
struct icst_vco {int v; int s; int r; } ;
struct clk_icst {int ctype; int /*<<< orphan*/  lockreg_off; int /*<<< orphan*/  map; int /*<<< orphan*/  vcoreg_off; } ;

/* Variables and functions */
#define  ICST_INTEGRATOR_AP_CM 131 
#define  ICST_INTEGRATOR_AP_SYS 130 
#define  ICST_INTEGRATOR_CP_CM_CORE 129 
#define  ICST_INTEGRATOR_CP_CM_MEM 128 
 int INTEGRATOR_AP_CM_BITS ; 
 int INTEGRATOR_AP_SYS_BITS ; 
 int INTEGRATOR_CP_CM_CORE_BITS ; 
 int INTEGRATOR_CP_CM_MEM_BITS ; 
 int VERSATILE_AUX_OSC_BITS ; 
 int /*<<< orphan*/  VERSATILE_LOCK_VAL ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vco_set(struct clk_icst *icst, struct icst_vco vco)
{
	u32 mask;
	u32 val;
	int ret;

	/* Mask the bits used by the VCO */
	switch (icst->ctype) {
	case ICST_INTEGRATOR_AP_CM:
		mask = INTEGRATOR_AP_CM_BITS;
		val = vco.v & 0xFF;
		if (vco.v & 0x100)
			pr_err("ICST error: tried to set bit 8 of VDW\n");
		if (vco.s != 1)
			pr_err("ICST error: tried to use VOD != 1\n");
		if (vco.r != 22)
			pr_err("ICST error: tried to use RDW != 22\n");
		break;
	case ICST_INTEGRATOR_AP_SYS:
		mask = INTEGRATOR_AP_SYS_BITS;
		val = vco.v & 0xFF;
		if (vco.v & 0x100)
			pr_err("ICST error: tried to set bit 8 of VDW\n");
		if (vco.s != 3)
			pr_err("ICST error: tried to use VOD != 1\n");
		if (vco.r != 46)
			pr_err("ICST error: tried to use RDW != 22\n");
		break;
	case ICST_INTEGRATOR_CP_CM_CORE:
		mask = INTEGRATOR_CP_CM_CORE_BITS; /* Uses 12 bits */
		val = (vco.v & 0xFF) | vco.s << 8;
		if (vco.v & 0x100)
			pr_err("ICST error: tried to set bit 8 of VDW\n");
		if (vco.r != 22)
			pr_err("ICST error: tried to use RDW != 22\n");
		break;
	case ICST_INTEGRATOR_CP_CM_MEM:
		mask = INTEGRATOR_CP_CM_MEM_BITS; /* Uses 12 bits */
		val = ((vco.v & 0xFF) << 12) | (vco.s << 20);
		if (vco.v & 0x100)
			pr_err("ICST error: tried to set bit 8 of VDW\n");
		if (vco.r != 22)
			pr_err("ICST error: tried to use RDW != 22\n");
		break;
	default:
		/* Regular auxilary oscillator */
		mask = VERSATILE_AUX_OSC_BITS;
		val = vco.v | (vco.r << 9) | (vco.s << 16);
		break;
	}

	pr_debug("ICST: new val = 0x%08x\n", val);

	/* This magic unlocks the VCO so it can be controlled */
	ret = regmap_write(icst->map, icst->lockreg_off, VERSATILE_LOCK_VAL);
	if (ret)
		return ret;
	ret = regmap_update_bits(icst->map, icst->vcoreg_off, mask, val);
	if (ret)
		return ret;
	/* This locks the VCO again */
	ret = regmap_write(icst->map, icst->lockreg_off, 0);
	if (ret)
		return ret;
	return 0;
}