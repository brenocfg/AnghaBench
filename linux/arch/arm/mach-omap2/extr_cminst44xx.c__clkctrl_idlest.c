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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int OMAP4430_IDLEST_MASK ; 
 int OMAP4430_IDLEST_SHIFT ; 
 int omap4_cminst_read_inst_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 _clkctrl_idlest(u8 part, u16 inst, u16 clkctrl_offs)
{
	u32 v = omap4_cminst_read_inst_reg(part, inst, clkctrl_offs);
	v &= OMAP4430_IDLEST_MASK;
	v >>= OMAP4430_IDLEST_SHIFT;
	return v;
}