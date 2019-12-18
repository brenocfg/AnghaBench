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
typedef  int uint32_t ;
struct clock_event_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ tmr_regs; } ;

/* Variables and functions */
 scalar_t__ KONA_GPTIMER_STCM0_OFFSET ; 
 int KONA_GPTIMER_STCS_COMPARE_ENABLE_SHIFT ; 
 scalar_t__ KONA_GPTIMER_STCS_OFFSET ; 
 int kona_timer_get_counter (scalar_t__,int*,int*) ; 
 int readl (scalar_t__) ; 
 TYPE_1__ timers ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int kona_timer_set_next_event(unsigned long clc,
				  struct clock_event_device *unused)
{
	/*
	 * timer (0) is disabled by the timer interrupt already
	 * so, here we reload the next event value and re-enable
	 * the timer.
	 *
	 * This way, we are potentially losing the time between
	 * timer-interrupt->set_next_event. CPU local timers, when
	 * they come in should get rid of skew.
	 */

	uint32_t lsw, msw;
	uint32_t reg;
	int ret;

	ret = kona_timer_get_counter(timers.tmr_regs, &msw, &lsw);
	if (ret)
		return ret;

	/* Load the "next" event tick value */
	writel(lsw + clc, timers.tmr_regs + KONA_GPTIMER_STCM0_OFFSET);

	/* Enable compare */
	reg = readl(timers.tmr_regs + KONA_GPTIMER_STCS_OFFSET);
	reg |= (1 << KONA_GPTIMER_STCS_COMPARE_ENABLE_SHIFT);
	writel(reg, timers.tmr_regs + KONA_GPTIMER_STCS_OFFSET);

	return 0;
}