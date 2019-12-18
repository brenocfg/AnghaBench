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
 int /*<<< orphan*/  U300_TIMER_APP_DGPT1_TIMER_DISABLE ; 
 scalar_t__ U300_TIMER_APP_GPT1IE ; 
 int /*<<< orphan*/  U300_TIMER_APP_GPT1IE_IRQ_DISABLE ; 
 scalar_t__ u300_timer_base ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int u300_shutdown(struct clock_event_device *evt)
{
	/* Disable interrupts on GP1 */
	writel(U300_TIMER_APP_GPT1IE_IRQ_DISABLE,
	       u300_timer_base + U300_TIMER_APP_GPT1IE);
	/* Disable GP1 */
	writel(U300_TIMER_APP_DGPT1_TIMER_DISABLE,
	       u300_timer_base + U300_TIMER_APP_DGPT1);
	return 0;
}