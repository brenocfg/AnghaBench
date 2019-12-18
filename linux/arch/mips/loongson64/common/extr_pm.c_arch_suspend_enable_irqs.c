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
 int /*<<< orphan*/  LOONGSON_INTENSET ; 
 int /*<<< orphan*/  PIC_MASTER_IMR ; 
 int /*<<< orphan*/  PIC_SLAVE_IMR ; 
 int /*<<< orphan*/  cached_bonito_irq_mask ; 
 int /*<<< orphan*/  cached_master_mask ; 
 int /*<<< orphan*/  cached_slave_mask ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void arch_suspend_enable_irqs(void)
{
	/* enable all mips events */
	local_irq_enable();
#ifdef CONFIG_I8259
	/* only enable the cached events of i8259A */
	outb(cached_slave_mask, PIC_SLAVE_IMR);
	outb(cached_master_mask, PIC_MASTER_IMR);
#endif
	/* enable all cached events of bonito */
	LOONGSON_INTENSET = cached_bonito_irq_mask;
	(void)LOONGSON_INTENSET;
}