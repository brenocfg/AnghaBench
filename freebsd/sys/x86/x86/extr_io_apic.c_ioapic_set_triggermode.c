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
typedef  enum intr_trigger { ____Placeholder_intr_trigger } intr_trigger ;
struct TYPE_2__ {scalar_t__ io_irq; int io_edgetrigger; } ;

/* Variables and functions */
 int EINVAL ; 
 int INTR_TRIGGER_CONFORM ; 
 int INTR_TRIGGER_EDGE ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  printf (char*,int,size_t,char*) ; 

int
ioapic_set_triggermode(void *cookie, u_int pin, enum intr_trigger trigger)
{
	struct ioapic *io;
	int edgetrigger;

	io = (struct ioapic *)cookie;
	if (pin >= io->io_numintr || trigger == INTR_TRIGGER_CONFORM)
		return (EINVAL);
	if (io->io_pins[pin].io_irq < 0)
		return (EINVAL);
	edgetrigger = (trigger == INTR_TRIGGER_EDGE);
	if (io->io_pins[pin].io_edgetrigger == edgetrigger)
		return (0);
	io->io_pins[pin].io_edgetrigger = edgetrigger;
	if (bootverbose)
		printf("ioapic%u: intpin %d trigger: %s\n", io->io_id, pin,
		    trigger == INTR_TRIGGER_EDGE ? "edge" : "level");
	return (0);
}