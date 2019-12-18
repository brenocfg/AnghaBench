#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* event_handler ) (TYPE_2__*) ;} ;
struct TYPE_3__ {scalar_t__ base; } ;
struct sun5i_timer_clkevt {TYPE_2__ clkevt; TYPE_1__ timer; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ TIMER_IRQ_ST_REG ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t sun5i_timer_interrupt(int irq, void *dev_id)
{
	struct sun5i_timer_clkevt *ce = (struct sun5i_timer_clkevt *)dev_id;

	writel(0x1, ce->timer.base + TIMER_IRQ_ST_REG);
	ce->clkevt.event_handler(&ce->clkevt);

	return IRQ_HANDLED;
}