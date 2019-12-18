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
 int /*<<< orphan*/  MCFSLT_SSR ; 
 int MCFSLT_SSR_BE ; 
 int MCFSLT_SSR_TE ; 
 int /*<<< orphan*/  TA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcfslt_cnt ; 
 scalar_t__ mcfslt_cycles_per_jiffy ; 
 int /*<<< orphan*/  timer_interrupt (int,void*) ; 

__attribute__((used)) static irqreturn_t mcfslt_tick(int irq, void *dummy)
{
	/* Reset Slice Timer 0 */
	__raw_writel(MCFSLT_SSR_BE | MCFSLT_SSR_TE, TA(MCFSLT_SSR));
	mcfslt_cnt += mcfslt_cycles_per_jiffy;
	return timer_interrupt(irq, dummy);
}