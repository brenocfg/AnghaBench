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
typedef  int /*<<< orphan*/  irq_handler_t ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  MCFSLT_SCR ; 
 int MCFSLT_SCR_IEN ; 
 int MCFSLT_SCR_RUN ; 
 int MCFSLT_SCR_TEN ; 
 int /*<<< orphan*/  MCFSLT_STCNT ; 
 int MCF_BUSCLK ; 
 int /*<<< orphan*/  MCF_IRQ_TIMER ; 
 int /*<<< orphan*/  TA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clocksource_register_hz (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mcfslt_clk ; 
 int mcfslt_cnt ; 
 int mcfslt_cycles_per_jiffy ; 
 int /*<<< orphan*/  mcfslt_profile_init () ; 
 int /*<<< orphan*/  mcfslt_timer_irq ; 
 int /*<<< orphan*/  setup_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_interrupt ; 

void hw_timer_init(irq_handler_t handler)
{
	mcfslt_cycles_per_jiffy = MCF_BUSCLK / HZ;
	/*
	 *	The coldfire slice timer (SLT) runs from STCNT to 0 included,
	 *	then STCNT again and so on.  It counts thus actually
	 *	STCNT + 1 steps for 1 tick, not STCNT.  So if you want
	 *	n cycles, initialize STCNT with n - 1.
	 */
	__raw_writel(mcfslt_cycles_per_jiffy - 1, TA(MCFSLT_STCNT));
	__raw_writel(MCFSLT_SCR_RUN | MCFSLT_SCR_IEN | MCFSLT_SCR_TEN,
								TA(MCFSLT_SCR));
	/* initialize mcfslt_cnt knowing that slice timers count down */
	mcfslt_cnt = mcfslt_cycles_per_jiffy;

	timer_interrupt = handler;
	setup_irq(MCF_IRQ_TIMER, &mcfslt_timer_irq);

	clocksource_register_hz(&mcfslt_clk, MCF_BUSCLK);

#ifdef CONFIG_HIGHPROFILE
	mcfslt_profile_init();
#endif
}