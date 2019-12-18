#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  (* event_handler ) (TYPE_1__*) ;} ;
struct davinci_clockevent {TYPE_1__ dev; int /*<<< orphan*/  base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  clockevent_state_oneshot (TYPE_1__*) ; 
 int /*<<< orphan*/  davinci_tim12_shutdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static irqreturn_t davinci_timer_irq_timer(int irq, void *data)
{
	struct davinci_clockevent *clockevent = data;

	if (!clockevent_state_oneshot(&clockevent->dev))
		davinci_tim12_shutdown(clockevent->base);

	clockevent->dev.event_handler(&clockevent->dev);

	return IRQ_HANDLED;
}