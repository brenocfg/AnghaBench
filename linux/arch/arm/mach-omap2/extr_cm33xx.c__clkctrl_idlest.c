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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int AM33XX_IDLEST_MASK ; 
 int AM33XX_IDLEST_SHIFT ; 
 int am33xx_cm_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 _clkctrl_idlest(u16 inst, u16 clkctrl_offs)
{
	u32 v = am33xx_cm_read_reg(inst, clkctrl_offs);
	v &= AM33XX_IDLEST_MASK;
	v >>= AM33XX_IDLEST_SHIFT;
	return v;
}