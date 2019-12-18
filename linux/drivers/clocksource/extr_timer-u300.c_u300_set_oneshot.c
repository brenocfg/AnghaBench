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
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ U300_TIMER_APP_DGPT1 ; 
 int U300_TIMER_APP_DGPT1_TIMER_DISABLE ; 
 scalar_t__ U300_TIMER_APP_EGPT1 ; 
 int U300_TIMER_APP_EGPT1_TIMER_ENABLE ; 
 scalar_t__ U300_TIMER_APP_GPT1IE ; 
 int U300_TIMER_APP_GPT1IE_IRQ_DISABLE ; 
 int U300_TIMER_APP_GPT1IE_IRQ_ENABLE ; 
 scalar_t__ U300_TIMER_APP_GPT1TC ; 
 scalar_t__ U300_TIMER_APP_SGPT1M ; 
 int U300_TIMER_APP_SGPT1M_MODE_ONE_SHOT ; 
 scalar_t__ u300_timer_base ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int u300_set_oneshot(struct clock_event_device *evt)
{
	/* Just return; here? */
	/*
	 * The actual event will be programmed by the next event hook,
	 * so we just set a dummy value somewhere at the end of the
	 * universe here.
	 */
	/* Disable interrupts on GPT1 */
	writel(U300_TIMER_APP_GPT1IE_IRQ_DISABLE,
	       u300_timer_base + U300_TIMER_APP_GPT1IE);
	/* Disable GP1 while we're reprogramming it. */
	writel(U300_TIMER_APP_DGPT1_TIMER_DISABLE,
	       u300_timer_base + U300_TIMER_APP_DGPT1);
	/*
	 * Expire far in the future, u300_set_next_event() will be
	 * called soon...
	 */
	writel(0xFFFFFFFF, u300_timer_base + U300_TIMER_APP_GPT1TC);
	/* We run one shot per tick here! */
	writel(U300_TIMER_APP_SGPT1M_MODE_ONE_SHOT,
	       u300_timer_base + U300_TIMER_APP_SGPT1M);
	/* Enable interrupts for this timer */
	writel(U300_TIMER_APP_GPT1IE_IRQ_ENABLE,
	       u300_timer_base + U300_TIMER_APP_GPT1IE);
	/* Enable timer */
	writel(U300_TIMER_APP_EGPT1_TIMER_ENABLE,
	       u300_timer_base + U300_TIMER_APP_EGPT1);
	return 0;
}