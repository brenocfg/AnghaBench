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
struct davinci_clockevent {int /*<<< orphan*/  base; } ;
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAVINCI_TIMER_REG_TIM12 ; 
 int /*<<< orphan*/  davinci_clockevent_write (struct davinci_clockevent*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  davinci_tim12_set_oneshot (int /*<<< orphan*/ ) ; 
 struct davinci_clockevent* to_davinci_clockevent (struct clock_event_device*) ; 

__attribute__((used)) static int davinci_clockevent_set_oneshot(struct clock_event_device *dev)
{
	struct davinci_clockevent *clockevent = to_davinci_clockevent(dev);

	davinci_clockevent_write(clockevent, DAVINCI_TIMER_REG_TIM12, 0x0);

	davinci_tim12_set_oneshot(clockevent->base);

	return 0;
}