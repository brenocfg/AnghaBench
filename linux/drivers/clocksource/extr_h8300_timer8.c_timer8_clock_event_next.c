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
struct timer8_priv {int dummy; } ;
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct timer8_priv* ced_to_priv (struct clock_event_device*) ; 
 int /*<<< orphan*/  clockevent_state_oneshot (struct clock_event_device*) ; 
 int /*<<< orphan*/  timer8_set_next (struct timer8_priv*,unsigned long) ; 

__attribute__((used)) static int timer8_clock_event_next(unsigned long delta,
				   struct clock_event_device *ced)
{
	struct timer8_priv *p = ced_to_priv(ced);

	BUG_ON(!clockevent_state_oneshot(ced));
	timer8_set_next(p, delta - 1);

	return 0;
}