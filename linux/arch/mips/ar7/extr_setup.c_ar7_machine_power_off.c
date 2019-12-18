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
 int /*<<< orphan*/  AR7_REGS_POWER ; 
 int /*<<< orphan*/  ar7_machine_halt () ; 
 scalar_t__ ioremap (int /*<<< orphan*/ ,int) ; 
 int readl (int*) ; 
 int /*<<< orphan*/  writel (int,int*) ; 

__attribute__((used)) static void ar7_machine_power_off(void)
{
	u32 *power_reg = (u32 *)ioremap(AR7_REGS_POWER, 1);
	u32 power_state = readl(power_reg) | (3 << 30);

	writel(power_state, power_reg);
	ar7_machine_halt();
}