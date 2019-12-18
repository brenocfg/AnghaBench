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
typedef  int /*<<< orphan*/  u32 ;
struct timer_of {int dummy; } ;
struct clock_event_device {int /*<<< orphan*/  (* event_handler ) (struct clock_event_device*) ;} ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ MLB_TMR_EVT_TMCSR_OFS ; 
 int /*<<< orphan*/  MLB_TMR_TMCSR_UF ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct clock_event_device*) ; 
 scalar_t__ timer_of_base (struct timer_of*) ; 
 struct timer_of* to_timer_of (struct clock_event_device*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t mlb_timer_interrupt(int irq, void *dev_id)
{
	struct clock_event_device *clk = dev_id;
	struct timer_of *to = to_timer_of(clk);
	u32 val;

	val = readl_relaxed(timer_of_base(to) + MLB_TMR_EVT_TMCSR_OFS);
	val &= ~MLB_TMR_TMCSR_UF;
	writel_relaxed(val, timer_of_base(to) + MLB_TMR_EVT_TMCSR_OFS);

	clk->event_handler(clk);

	return IRQ_HANDLED;
}