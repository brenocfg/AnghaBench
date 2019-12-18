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
 int /*<<< orphan*/  LOONGSON_INTEN ; 
 int LOONGSON_INTENCLR ; 
 int /*<<< orphan*/  PIC_MASTER_IMR ; 
 int /*<<< orphan*/  PIC_SLAVE_IMR ; 
 int /*<<< orphan*/  cached_bonito_irq_mask ; 
 void* cached_master_mask ; 
 void* cached_slave_mask ; 
 void* inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 

void arch_suspend_disable_irqs(void)
{
	/* disable all mips events */
	local_irq_disable();

#ifdef CONFIG_I8259
	/* disable all events of i8259A */
	cached_slave_mask = inb(PIC_SLAVE_IMR);
	cached_master_mask = inb(PIC_MASTER_IMR);

	outb(0xff, PIC_SLAVE_IMR);
	inb(PIC_SLAVE_IMR);
	outb(0xff, PIC_MASTER_IMR);
	inb(PIC_MASTER_IMR);
#endif
	/* disable all events of bonito */
	cached_bonito_irq_mask = LOONGSON_INTEN;
	LOONGSON_INTENCLR = 0xffff;
	(void)LOONGSON_INTENCLR;
}