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
struct pic {int dummy; } ;
struct ioapic_intsrc {scalar_t__ io_irq; int /*<<< orphan*/  io_intsrc; } ;
struct ioapic {int io_numintr; struct ioapic_intsrc* io_pins; } ;

/* Variables and functions */
 int /*<<< orphan*/  intr_register_source (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ioapic_register_sources(struct pic *pic)
{
	struct ioapic_intsrc *pin;
	struct ioapic *io;
	int i;

	io = (struct ioapic *)pic;
	for (i = 0, pin = io->io_pins; i < io->io_numintr; i++, pin++) {
		if (pin->io_irq >= 0)
			intr_register_source(&pin->io_intsrc);
	}
}