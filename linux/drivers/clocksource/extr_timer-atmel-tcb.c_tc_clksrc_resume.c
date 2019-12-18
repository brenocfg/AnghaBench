#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct clocksource {int dummy; } ;
struct TYPE_3__ {int cmr; int rc; int imr; scalar_t__ clken; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 scalar_t__ ATMEL_TC_BCR ; 
 scalar_t__ ATMEL_TC_BMR ; 
 int ATMEL_TC_CLKEN ; 
 scalar_t__ ATMEL_TC_REG (int,int /*<<< orphan*/ ) ; 
 int ATMEL_TC_SYNC ; 
 int /*<<< orphan*/  CCR ; 
 int /*<<< orphan*/  CMR ; 
 int /*<<< orphan*/  IDR ; 
 int /*<<< orphan*/  IER ; 
 int /*<<< orphan*/  RA ; 
 int /*<<< orphan*/  RB ; 
 int /*<<< orphan*/  RC ; 
 int bmr_cache ; 
 scalar_t__ tcaddr ; 
 TYPE_1__* tcb_cache ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void tc_clksrc_resume(struct clocksource *cs)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(tcb_cache); i++) {
		/* Restore registers for the channel, RA and RB are not used  */
		writel(tcb_cache[i].cmr, tcaddr + ATMEL_TC_REG(i, CMR));
		writel(tcb_cache[i].rc, tcaddr + ATMEL_TC_REG(i, RC));
		writel(0, tcaddr + ATMEL_TC_REG(i, RA));
		writel(0, tcaddr + ATMEL_TC_REG(i, RB));
		/* Disable all the interrupts */
		writel(0xff, tcaddr + ATMEL_TC_REG(i, IDR));
		/* Reenable interrupts that were enabled before suspending */
		writel(tcb_cache[i].imr, tcaddr + ATMEL_TC_REG(i, IER));
		/* Start the clock if it was used */
		if (tcb_cache[i].clken)
			writel(ATMEL_TC_CLKEN, tcaddr + ATMEL_TC_REG(i, CCR));
	}

	/* Dual channel, chain channels */
	writel(bmr_cache, tcaddr + ATMEL_TC_BMR);
	/* Finally, trigger all the channels*/
	writel(ATMEL_TC_SYNC, tcaddr + ATMEL_TC_BCR);
}