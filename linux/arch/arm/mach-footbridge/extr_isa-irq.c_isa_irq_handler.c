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
struct irq_desc {int dummy; } ;

/* Variables and functions */
 scalar_t__ PCIIACK_BASE ; 
 unsigned int _ISA_IRQ (int) ; 
 int /*<<< orphan*/  do_bad_IRQ (struct irq_desc*) ; 
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 

__attribute__((used)) static void isa_irq_handler(struct irq_desc *desc)
{
	unsigned int isa_irq = *(unsigned char *)PCIIACK_BASE;

	if (isa_irq < _ISA_IRQ(0) || isa_irq >= _ISA_IRQ(16)) {
		do_bad_IRQ(desc);
		return;
	}

	generic_handle_irq(isa_irq);
}