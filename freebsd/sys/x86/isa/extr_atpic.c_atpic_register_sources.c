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
struct pic {int dummy; } ;
struct atpic_intsrc {int /*<<< orphan*/  at_intsrc; } ;
struct atpic {int dummy; } ;

/* Variables and functions */
 int ICU_SLAVEID ; 
 size_t MASTER ; 
 int NUM_ISA_IRQS ; 
 struct atpic_intsrc* atintrs ; 
 struct atpic* atpics ; 
 int /*<<< orphan*/ * intr_lookup_source (int) ; 
 int /*<<< orphan*/  intr_register_source (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
atpic_register_sources(struct pic *pic)
{
	struct atpic *ap = (struct atpic *)pic;
	struct atpic_intsrc *ai;
	int i;

	/*
	 * If any of the ISA IRQs have an interrupt source already, then
	 * assume that the I/O APICs are being used and don't register any
	 * of our interrupt sources.  This makes sure we don't accidentally
	 * use mixed mode.  The "accidental" use could otherwise occur on
	 * machines that route the ACPI SCI interrupt to a different ISA
	 * IRQ (at least one machine routes it to IRQ 13) thus disabling
	 * that APIC ISA routing and allowing the ATPIC source for that IRQ
	 * to leak through.  We used to depend on this feature for routing
	 * IRQ0 via mixed mode, but now we don't use mixed mode at all.
	 *
	 * To avoid the slave not register sources after the master
	 * registers its sources, register all IRQs when this function is
	 * called on the master.
	 */
	if (ap != &atpics[MASTER])
		return;
	for (i = 0; i < NUM_ISA_IRQS; i++)
		if (intr_lookup_source(i) != NULL)
			return;

	/* Loop through all interrupt sources and add them. */
	for (i = 0, ai = atintrs; i < NUM_ISA_IRQS; i++, ai++) {
		if (i == ICU_SLAVEID)
			continue;
		intr_register_source(&ai->at_intsrc);
	}
}