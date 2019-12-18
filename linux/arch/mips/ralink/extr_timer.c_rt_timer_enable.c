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
struct rt_timer {int timer_freq; int timer_div; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIMER_REG_TMR0CTL ; 
 int /*<<< orphan*/  TIMER_REG_TMR0LOAD ; 
 int TMR0CTL_ENABLE ; 
 int rt_timer_r32 (struct rt_timer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt_timer_w32 (struct rt_timer*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rt_timer_enable(struct rt_timer *rt)
{
	u32 t;

	rt_timer_w32(rt, TIMER_REG_TMR0LOAD, rt->timer_freq / rt->timer_div);

	t = rt_timer_r32(rt, TIMER_REG_TMR0CTL);
	t |= TMR0CTL_ENABLE;
	rt_timer_w32(rt, TIMER_REG_TMR0CTL, t);

	return 0;
}