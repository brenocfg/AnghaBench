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
struct intsrc {int dummy; } ;
struct TYPE_2__ {scalar_t__ is_pic; int /*<<< orphan*/ * is_straycount; int /*<<< orphan*/ * is_count; } ;
struct atpic_intsrc {int /*<<< orphan*/  at_trigger; int /*<<< orphan*/  at_intr; int /*<<< orphan*/  at_intr_pti; scalar_t__ at_irq; TYPE_1__ at_intsrc; int /*<<< orphan*/  at_straycount; int /*<<< orphan*/  at_count; } ;
struct atpic {scalar_t__ at_intbase; } ;

/* Variables and functions */
 int /*<<< orphan*/  GSEL_ATPIC ; 
 size_t ICU_SLAVEID ; 
 int /*<<< orphan*/  INTR_TRIGGER_EDGE ; 
 int /*<<< orphan*/  INTR_TRIGGER_LEVEL ; 
 size_t MASTER ; 
 int NUM_ISA_IRQS ; 
 int /*<<< orphan*/  SDT_ATPIC ; 
 int /*<<< orphan*/  SEL_KPL ; 
 size_t SLAVE ; 
 struct atpic_intsrc* atintrs ; 
 int /*<<< orphan*/  atpic_enable_source (struct intsrc*) ; 
 int /*<<< orphan*/ * atpics ; 
 scalar_t__ elcr_found ; 
 int /*<<< orphan*/  elcr_read_trigger (int) ; 
 int /*<<< orphan*/  i8259_init (int /*<<< orphan*/ *,int) ; 
 scalar_t__ pti ; 
 int /*<<< orphan*/  setidt (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
atpic_startup(void)
{
	struct atpic_intsrc *ai;
	int i;

	/* Start off with all interrupts disabled. */
	i8259_init(&atpics[MASTER], 0);
	i8259_init(&atpics[SLAVE], 1);
	atpic_enable_source((struct intsrc *)&atintrs[ICU_SLAVEID]);

	/* Install low-level interrupt handlers for all of our IRQs. */
	for (i = 0, ai = atintrs; i < NUM_ISA_IRQS; i++, ai++) {
		if (i == ICU_SLAVEID)
			continue;
		ai->at_intsrc.is_count = &ai->at_count;
		ai->at_intsrc.is_straycount = &ai->at_straycount;
		setidt(((struct atpic *)ai->at_intsrc.is_pic)->at_intbase +
		    ai->at_irq, pti ? ai->at_intr_pti : ai->at_intr, SDT_ATPIC,
		    SEL_KPL, GSEL_ATPIC);
	}

	/*
	 * Look for an ELCR.  If we find one, update the trigger modes.
	 * If we don't find one, assume that IRQs 0, 1, 2, and 13 are
	 * edge triggered and that everything else is level triggered.
	 * We only use the trigger information to reprogram the ELCR if
	 * we have one and as an optimization to avoid masking edge
	 * triggered interrupts.  For the case that we don't have an ELCR,
	 * it doesn't hurt to mask an edge triggered interrupt, so we
	 * assume level trigger for any interrupt that we aren't sure is
	 * edge triggered.
	 */
	if (elcr_found) {
		for (i = 0, ai = atintrs; i < NUM_ISA_IRQS; i++, ai++)
			ai->at_trigger = elcr_read_trigger(i);
	} else {
		for (i = 0, ai = atintrs; i < NUM_ISA_IRQS; i++, ai++)
			switch (i) {
			case 0:
			case 1:
			case 2:
			case 8:
			case 13:
				ai->at_trigger = INTR_TRIGGER_EDGE;
				break;
			default:
				ai->at_trigger = INTR_TRIGGER_LEVEL;
				break;
			}
	}
}