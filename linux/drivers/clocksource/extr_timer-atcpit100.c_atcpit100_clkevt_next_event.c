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
typedef  unsigned long u32 ;
struct timer_of {int dummy; } ;
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 unsigned long CH0TMR0EN ; 
 scalar_t__ CH0_REL ; 
 scalar_t__ CH_EN ; 
 unsigned long readl (scalar_t__) ; 
 scalar_t__ timer_of_base (struct timer_of*) ; 
 struct timer_of* to_timer_of (struct clock_event_device*) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static int atcpit100_clkevt_next_event(unsigned long evt,
	struct clock_event_device *clkevt)
{
	u32 val;
	struct timer_of *to = to_timer_of(clkevt);

	val = readl(timer_of_base(to) + CH_EN);
	writel(val & ~CH0TMR0EN, timer_of_base(to) + CH_EN);
	writel(evt, timer_of_base(to) + CH0_REL);
	writel(val | CH0TMR0EN, timer_of_base(to) + CH_EN);

	return 0;
}