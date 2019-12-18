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

/* Variables and functions */
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  reset_ctrl_regs (unsigned int) ; 

__attribute__((used)) static int dbg_reset_online(unsigned int cpu)
{
	local_irq_disable();
	reset_ctrl_regs(cpu);
	local_irq_enable();
	return 0;
}