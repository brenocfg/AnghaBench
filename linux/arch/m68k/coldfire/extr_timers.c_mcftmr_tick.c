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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  MCFTIMER_TER ; 
 int MCFTIMER_TER_CAP ; 
 int MCFTIMER_TER_REF ; 
 int /*<<< orphan*/  TA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writeb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcftmr_cnt ; 
 scalar_t__ mcftmr_cycles_per_jiffy ; 
 int /*<<< orphan*/  timer_interrupt (int,void*) ; 

__attribute__((used)) static irqreturn_t mcftmr_tick(int irq, void *dummy)
{
	/* Reset the ColdFire timer */
	__raw_writeb(MCFTIMER_TER_CAP | MCFTIMER_TER_REF, TA(MCFTIMER_TER));

	mcftmr_cnt += mcftmr_cycles_per_jiffy;
	return timer_interrupt(irq, dummy);
}