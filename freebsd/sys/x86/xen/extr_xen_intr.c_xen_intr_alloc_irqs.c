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
 scalar_t__ NR_EVENT_CHANNELS ; 
 scalar_t__ UINT_MAX ; 
 scalar_t__ first_evtchn_irq ; 
 scalar_t__ num_io_irqs ; 
 int /*<<< orphan*/  panic (char*) ; 

void
xen_intr_alloc_irqs(void)
{

	if (num_io_irqs > UINT_MAX - NR_EVENT_CHANNELS)
		panic("IRQ allocation overflow (num_msi_irqs too high?)");
	first_evtchn_irq = num_io_irqs;
	num_io_irqs += NR_EVENT_CHANNELS;
}