#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int slot; int bus; int /*<<< orphan*/  devfunc; } ;
typedef  TYPE_1__ pir_entry_t ;

/* Variables and functions */
 int PIR_DEV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_print_irqmask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
print_irq_line(int entry, pir_entry_t *p, char line, uint8_t link,
    uint16_t irqs)
{

	if (link == 0)
		return;

	printf("%3d    ", entry);
	if (p->slot == 0)
		printf("embedded ");
	else
		printf("slot %-3d ", p->slot);

	printf(" %3d  %3d    %c   0x%02x  ", p->bus, PIR_DEV(p->devfunc),
	    line, link);
	pci_print_irqmask(irqs);
	printf("\n");
}