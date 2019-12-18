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
 int /*<<< orphan*/  JMR3927_IOC_RESET_ADDR ; 
 int /*<<< orphan*/  JMR3927_IOC_RESET_CPU ; 
 int /*<<< orphan*/  JMR3927_IOC_RESET_PCI ; 
 int /*<<< orphan*/  _machine_halt () ; 
 int /*<<< orphan*/  jmr3927_ioc_reg_in (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jmr3927_ioc_reg_out (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void jmr3927_machine_restart(char *command)
{
	local_irq_disable();
#if 1	/* Resetting PCI bus */
	jmr3927_ioc_reg_out(0, JMR3927_IOC_RESET_ADDR);
	jmr3927_ioc_reg_out(JMR3927_IOC_RESET_PCI, JMR3927_IOC_RESET_ADDR);
	(void)jmr3927_ioc_reg_in(JMR3927_IOC_RESET_ADDR);	/* flush WB */
	mdelay(1);
	jmr3927_ioc_reg_out(0, JMR3927_IOC_RESET_ADDR);
#endif
	jmr3927_ioc_reg_out(JMR3927_IOC_RESET_CPU, JMR3927_IOC_RESET_ADDR);
	/* fallback */
	(*_machine_halt)();
}