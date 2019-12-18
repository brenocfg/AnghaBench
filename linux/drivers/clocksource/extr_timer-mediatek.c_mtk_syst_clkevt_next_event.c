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
struct timer_of {int dummy; } ;
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 unsigned long SYST_CON_EN ; 
 unsigned long SYST_CON_IRQ_EN ; 
 int /*<<< orphan*/  SYST_CON_REG (struct timer_of*) ; 
 int /*<<< orphan*/  SYST_VAL_REG (struct timer_of*) ; 
 struct timer_of* to_timer_of (struct clock_event_device*) ; 
 int /*<<< orphan*/  writel (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_syst_clkevt_next_event(unsigned long ticks,
				      struct clock_event_device *clkevt)
{
	struct timer_of *to = to_timer_of(clkevt);

	/* Enable clock to allow timeout tick update later */
	writel(SYST_CON_EN, SYST_CON_REG(to));

	/*
	 * Write new timeout ticks. Timer shall start countdown
	 * after timeout ticks are updated.
	 */
	writel(ticks, SYST_VAL_REG(to));

	/* Enable interrupt */
	writel(SYST_CON_EN | SYST_CON_IRQ_EN, SYST_CON_REG(to));

	return 0;
}