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
struct davinci_clockevent {int /*<<< orphan*/  cmp_off; } ;
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAVINCI_TIMER_REG_TIM12 ; 
 unsigned int davinci_clockevent_read (struct davinci_clockevent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  davinci_clockevent_write (struct davinci_clockevent*,int /*<<< orphan*/ ,unsigned int) ; 
 struct davinci_clockevent* to_davinci_clockevent (struct clock_event_device*) ; 

__attribute__((used)) static int
davinci_clockevent_set_next_event_cmp(unsigned long cycles,
				      struct clock_event_device *dev)
{
	struct davinci_clockevent *clockevent = to_davinci_clockevent(dev);
	unsigned int curr_time;

	curr_time = davinci_clockevent_read(clockevent,
					    DAVINCI_TIMER_REG_TIM12);
	davinci_clockevent_write(clockevent,
				 clockevent->cmp_off, curr_time + cycles);

	return 0;
}