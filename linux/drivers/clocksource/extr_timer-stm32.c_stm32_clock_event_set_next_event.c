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
 int ETIME ; 
 scalar_t__ TIM_CCR1 ; 
 scalar_t__ TIM_CNT ; 
 scalar_t__ TIM_DIER ; 
 unsigned long TIM_DIER_CC1IE ; 
 unsigned long readl_relaxed (scalar_t__) ; 
 scalar_t__ timer_of_base (struct timer_of*) ; 
 struct timer_of* to_timer_of (struct clock_event_device*) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned long,scalar_t__) ; 

__attribute__((used)) static int stm32_clock_event_set_next_event(unsigned long evt,
					    struct clock_event_device *clkevt)
{
	struct timer_of *to = to_timer_of(clkevt);
	unsigned long now, next;

	next = readl_relaxed(timer_of_base(to) + TIM_CNT) + evt;
	writel_relaxed(next, timer_of_base(to) + TIM_CCR1);
	now = readl_relaxed(timer_of_base(to) + TIM_CNT);

	if ((next - now) > evt)
		return -ETIME;

	writel_relaxed(TIM_DIER_CC1IE, timer_of_base(to) + TIM_DIER);

	return 0;
}