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
typedef  int /*<<< orphan*/  u8 ;
struct clk_omap_reg {int offset; } ;
struct clk_hw_omap {int /*<<< orphan*/  enable_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP3430ES2_ST_DSS_IDLE_SHIFT ; 
 int /*<<< orphan*/  OMAP34XX_CM_IDLEST_VAL ; 
 int /*<<< orphan*/  memcpy (struct clk_omap_reg*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
omap3430es2_clk_dss_usbhost_find_idlest(struct clk_hw_omap *clk,
					struct clk_omap_reg *idlest_reg,
					u8 *idlest_bit, u8 *idlest_val)
{
	memcpy(idlest_reg, &clk->enable_reg, sizeof(*idlest_reg));

	idlest_reg->offset &= ~0xf0;
	idlest_reg->offset |= 0x20;
	/* USBHOST_IDLE has same shift */
	*idlest_bit = OMAP3430ES2_ST_DSS_IDLE_SHIFT;
	*idlest_val = OMAP34XX_CM_IDLEST_VAL;
}