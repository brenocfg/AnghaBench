#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_8__ {int istat; } ;
struct TYPE_5__ {unsigned long istat; } ;
struct TYPE_6__ {TYPE_1__ ctrl; } ;
struct TYPE_7__ {TYPE_2__ perif; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int CRIME_MACEISA_INT_MASK ; 
 int CRIME_VICE_IRQ ; 
 int MACEISA_AUDIO_SW_IRQ ; 
 int MACEISA_SERIAL2_RDMAOR_IRQ ; 
 int MACE_VID_IN1_IRQ ; 
 int __ffs (unsigned long) ; 
 TYPE_4__* crime ; 
 int crime_mask ; 
 int /*<<< orphan*/  do_IRQ (int) ; 
 TYPE_3__* mace ; 
 unsigned long maceisa_mask ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void ip32_irq0(void)
{
	uint64_t crime_int;
	int irq = 0;

	/*
	 * Sanity check interrupt numbering enum.
	 * MACE got 32 interrupts and there are 32 MACE ISA interrupts daisy
	 * chained.
	 */
	BUILD_BUG_ON(CRIME_VICE_IRQ - MACE_VID_IN1_IRQ != 31);
	BUILD_BUG_ON(MACEISA_SERIAL2_RDMAOR_IRQ - MACEISA_AUDIO_SW_IRQ != 31);

	crime_int = crime->istat & crime_mask;

	/* crime sometime delivers spurious interrupts, ignore them */
	if (unlikely(crime_int == 0))
		return;

	irq = MACE_VID_IN1_IRQ + __ffs(crime_int);

	if (crime_int & CRIME_MACEISA_INT_MASK) {
		unsigned long mace_int = mace->perif.ctrl.istat;
		irq = __ffs(mace_int & maceisa_mask) + MACEISA_AUDIO_SW_IRQ;
	}

	pr_debug("*irq %u*\n", irq);
	do_IRQ(irq);
}