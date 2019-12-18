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
struct timer_of {TYPE_1__ clkevt; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  PTIM_TSR ; 
 int /*<<< orphan*/  csky_to ; 
 int /*<<< orphan*/  mtcr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 struct timer_of* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t csky_timer_interrupt(int irq, void *dev)
{
	struct timer_of *to = this_cpu_ptr(&csky_to);

	mtcr(PTIM_TSR, 0);

	to->clkevt.event_handler(&to->clkevt);

	return IRQ_HANDLED;
}