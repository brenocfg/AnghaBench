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
struct intsrc {int /*<<< orphan*/ * is_pic; } ;
struct atpic_intsrc {scalar_t__ at_trigger; } ;
struct atpic {int /*<<< orphan*/  at_imen; scalar_t__ at_ioaddr; } ;
struct TYPE_2__ {int /*<<< orphan*/  at_pic; } ;

/* Variables and functions */
 scalar_t__ ICU_IMR_OFFSET ; 
 int /*<<< orphan*/  IMEN_MASK (struct atpic_intsrc*) ; 
 scalar_t__ INTR_TRIGGER_EDGE ; 
 size_t MASTER ; 
 int PIC_EOI ; 
 int /*<<< orphan*/  _atpic_eoi_master (struct intsrc*) ; 
 int /*<<< orphan*/  _atpic_eoi_slave (struct intsrc*) ; 
 TYPE_1__* atpics ; 
 int /*<<< orphan*/  outb (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spinlock_enter () ; 
 int /*<<< orphan*/  spinlock_exit () ; 

__attribute__((used)) static void
atpic_disable_source(struct intsrc *isrc, int eoi)
{
	struct atpic_intsrc *ai = (struct atpic_intsrc *)isrc;
	struct atpic *ap = (struct atpic *)isrc->is_pic;

	spinlock_enter();
	if (ai->at_trigger != INTR_TRIGGER_EDGE) {
		ap->at_imen |= IMEN_MASK(ai);
		outb(ap->at_ioaddr + ICU_IMR_OFFSET, ap->at_imen);
	}

	/*
	 * Take care to call these functions directly instead of through
	 * a function pointer.  All of the referenced variables should
	 * still be hot in the cache.
	 */
	if (eoi == PIC_EOI) {
		if (isrc->is_pic == &atpics[MASTER].at_pic)
			_atpic_eoi_master(isrc);
		else
			_atpic_eoi_slave(isrc);
	}

	spinlock_exit();
}