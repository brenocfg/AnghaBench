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
 int /*<<< orphan*/  handle_irq (int) ; 

__attribute__((used)) static void 
rawhide_srm_device_interrupt(unsigned long vector)
{
	int irq;

	irq = (vector - 0x800) >> 4;

        /*
         * The RAWHIDE SRM console reports PCI interrupts with a vector
	 * 0x80 *higher* than one might expect, as PCI IRQ 0 (ie bit 0)
	 * shows up as IRQ 24, etc, etc. We adjust it down by 8 to have
	 * it line up with the actual bit numbers from the REQ registers,
	 * which is how we manage the interrupts/mask. Sigh...
	 *
	 * Also, PCI #1 interrupts are offset some more... :-(
         */

	if (irq == 52) {
		/* SCSI on PCI1 is special.  */
		irq = 72;
	}

	/* Adjust by which hose it is from.  */
	irq -= ((irq + 16) >> 2) & 0x38;

	handle_irq(irq);
}