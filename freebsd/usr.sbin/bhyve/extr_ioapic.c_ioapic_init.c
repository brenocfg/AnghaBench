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
struct vmctx {int dummy; } ;

/* Variables and functions */
 int pci_pins ; 
 scalar_t__ vm_ioapic_pincount (struct vmctx*,int*) ; 

void
ioapic_init(struct vmctx *ctx)
{

	if (vm_ioapic_pincount(ctx, &pci_pins) < 0) {
		pci_pins = 0;
		return;
	}

	/* Ignore the first 16 pins. */
	if (pci_pins <= 16) {
		pci_pins = 0;
		return;
	}
	pci_pins -= 16;
}