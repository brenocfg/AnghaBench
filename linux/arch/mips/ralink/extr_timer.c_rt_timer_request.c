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
typedef  int u32 ;
struct rt_timer {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIMER_REG_TMR0CTL ; 
 int TMR0CTL_MODE_PERIODIC ; 
 int TMR0CTL_PRESCALE_VAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rt_timer*) ; 
 int /*<<< orphan*/  rt_timer_irq ; 
 int /*<<< orphan*/  rt_timer_w32 (struct rt_timer*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rt_timer_request(struct rt_timer *rt)
{
	int err = request_irq(rt->irq, rt_timer_irq, 0,
						dev_name(rt->dev), rt);
	if (err) {
		dev_err(rt->dev, "failed to request irq\n");
	} else {
		u32 t = TMR0CTL_MODE_PERIODIC | TMR0CTL_PRESCALE_VAL;
		rt_timer_w32(rt, TIMER_REG_TMR0CTL, t);
	}
	return err;
}