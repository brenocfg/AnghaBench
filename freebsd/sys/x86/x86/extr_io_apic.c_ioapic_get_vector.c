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
struct ioapic {size_t io_numintr; TYPE_1__* io_pins; } ;
struct TYPE_2__ {int io_irq; } ;

/* Variables and functions */

int
ioapic_get_vector(void *cookie, u_int pin)
{
	struct ioapic *io;

	io = (struct ioapic *)cookie;
	if (pin >= io->io_numintr)
		return (-1);
	return (io->io_pins[pin].io_irq);
}