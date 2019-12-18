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
 int /*<<< orphan*/  disable_irq_nosync (unsigned int) ; 
 int /*<<< orphan*/  enable_irq (unsigned int) ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  i8259A_chip ; 
 int io_apic_irqs ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lapic_assign_legacy_vector (unsigned int,int) ; 

__attribute__((used)) static void make_8259A_irq(unsigned int irq)
{
	disable_irq_nosync(irq);
	io_apic_irqs &= ~(1<<irq);
	irq_set_chip_and_handler(irq, &i8259A_chip, handle_level_irq);
	enable_irq(irq);
	lapic_assign_legacy_vector(irq, true);
}