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
typedef  enum intr_polarity { ____Placeholder_intr_polarity } intr_polarity ;
struct TYPE_2__ {scalar_t__ io_irq; int io_activehi; } ;

/* Variables and functions */
 int EINVAL ; 
 int INTR_POLARITY_CONFORM ; 
 int INTR_POLARITY_HIGH ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  printf (char*,int,size_t,char*) ; 

int
ioapic_set_polarity(void *cookie, u_int pin, enum intr_polarity pol)
{
	struct ioapic *io;
	int activehi;

	io = (struct ioapic *)cookie;
	if (pin >= io->io_numintr || pol == INTR_POLARITY_CONFORM)
		return (EINVAL);
	if (io->io_pins[pin].io_irq < 0)
		return (EINVAL);
	activehi = (pol == INTR_POLARITY_HIGH);
	if (io->io_pins[pin].io_activehi == activehi)
		return (0);
	io->io_pins[pin].io_activehi = activehi;
	if (bootverbose)
		printf("ioapic%u: intpin %d polarity: %s\n", io->io_id, pin,
		    pol == INTR_POLARITY_HIGH ? "high" : "low");
	return (0);
}