#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct ioapic {size_t io_numintr; int io_id; TYPE_1__* io_pins; } ;
struct TYPE_2__ {scalar_t__ io_irq; int io_edgetrigger; int io_activehi; scalar_t__ io_masked; int /*<<< orphan*/  io_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_BUS_UNKNOWN ; 
 int EINVAL ; 
 scalar_t__ IRQ_SMI ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  printf (char*,int,size_t) ; 

int
ioapic_set_smi(void *cookie, u_int pin)
{
	struct ioapic *io;

	io = (struct ioapic *)cookie;
	if (pin >= io->io_numintr)
		return (EINVAL);
	if (io->io_pins[pin].io_irq == IRQ_SMI)
		return (0);
	if (io->io_pins[pin].io_irq < 0)
		return (EINVAL);
	io->io_pins[pin].io_bus = APIC_BUS_UNKNOWN;
	io->io_pins[pin].io_irq = IRQ_SMI;
	io->io_pins[pin].io_masked = 0;
	io->io_pins[pin].io_edgetrigger = 1;
	io->io_pins[pin].io_activehi = 1;
	if (bootverbose)
		printf("ioapic%u: Routing SMI -> intpin %d\n",
		    io->io_id, pin);
	return (0);
}