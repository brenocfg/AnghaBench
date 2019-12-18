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
struct ioapic_intsrc {int io_irq; int /*<<< orphan*/  io_bus; } ;

/* Variables and functions */
#define  IRQ_DISABLED 131 
#define  IRQ_EXTINT 130 
#define  IRQ_NMI 129 
#define  IRQ_SMI 128 
 char* ioapic_bus_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
ioapic_print_irq(struct ioapic_intsrc *intpin)
{

	switch (intpin->io_irq) {
	case IRQ_DISABLED:
		printf("disabled");
		break;
	case IRQ_EXTINT:
		printf("ExtINT");
		break;
	case IRQ_NMI:
		printf("NMI");
		break;
	case IRQ_SMI:
		printf("SMI");
		break;
	default:
		printf("%s IRQ %d", ioapic_bus_string(intpin->io_bus),
		    intpin->io_irq);
	}
}