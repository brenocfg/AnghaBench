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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int find_irq_entry (int,int,int /*<<< orphan*/ ) ; 
 int irq_polarity (int) ; 
 int irq_trigger (int) ; 
 int /*<<< orphan*/  mp_INT ; 
 int mp_find_ioapic (int /*<<< orphan*/ ) ; 
 int mp_find_ioapic_pin (int,int /*<<< orphan*/ ) ; 
 scalar_t__ skip_ioapic_setup ; 

int acpi_get_override_irq(u32 gsi, int *trigger, int *polarity)
{
	int ioapic, pin, idx;

	if (skip_ioapic_setup)
		return -1;

	ioapic = mp_find_ioapic(gsi);
	if (ioapic < 0)
		return -1;

	pin = mp_find_ioapic_pin(ioapic, gsi);
	if (pin < 0)
		return -1;

	idx = find_irq_entry(ioapic, pin, mp_INT);
	if (idx < 0)
		return -1;

	*trigger = irq_trigger(idx);
	*polarity = irq_polarity(idx);
	return 0;
}