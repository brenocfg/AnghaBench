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
struct timer_of {int dummy; } ;
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 int CH0TMR0EN ; 
 scalar_t__ CH0_REL ; 
 scalar_t__ CH_EN ; 
 int readl (scalar_t__) ; 
 scalar_t__ timer_of_base (struct timer_of*) ; 
 struct timer_of* to_timer_of (struct clock_event_device*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int atcpit100_clkevt_set_oneshot(struct clock_event_device *evt)
{
	struct timer_of *to = to_timer_of(evt);
	u32 val;

	writel(~0x0, timer_of_base(to) + CH0_REL);
	val = readl(timer_of_base(to) + CH_EN);
	writel(val | CH0TMR0EN, timer_of_base(to) + CH_EN);

	return 0;
}