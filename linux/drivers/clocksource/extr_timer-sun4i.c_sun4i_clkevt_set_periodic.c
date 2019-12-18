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
 int /*<<< orphan*/  sun4i_clkevt_time_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sun4i_clkevt_time_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sun4i_clkevt_time_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_of_base (struct timer_of*) ; 
 int /*<<< orphan*/  timer_of_period (struct timer_of*) ; 
 struct timer_of* to_timer_of (struct clock_event_device*) ; 

__attribute__((used)) static int sun4i_clkevt_set_periodic(struct clock_event_device *evt)
{
	struct timer_of *to = to_timer_of(evt);

	sun4i_clkevt_time_stop(timer_of_base(to), 0);
	sun4i_clkevt_time_setup(timer_of_base(to), 0, timer_of_period(to));
	sun4i_clkevt_time_start(timer_of_base(to), 0, true);

	return 0;
}