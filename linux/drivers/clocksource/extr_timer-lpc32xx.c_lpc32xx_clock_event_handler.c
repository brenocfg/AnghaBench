#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* event_handler ) (TYPE_1__*) ;} ;
struct lpc32xx_clock_event_ddata {TYPE_1__ evtdev; scalar_t__ base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ LPC32XX_TIMER_IR ; 
 int /*<<< orphan*/  LPC32XX_TIMER_IR_MR0INT ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t lpc32xx_clock_event_handler(int irq, void *dev_id)
{
	struct lpc32xx_clock_event_ddata *ddata = dev_id;

	/* Clear match on channel 0 */
	writel_relaxed(LPC32XX_TIMER_IR_MR0INT, ddata->base + LPC32XX_TIMER_IR);

	ddata->evtdev.event_handler(&ddata->evtdev);

	return IRQ_HANDLED;
}