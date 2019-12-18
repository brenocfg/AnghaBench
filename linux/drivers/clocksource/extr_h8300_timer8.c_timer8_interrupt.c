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
struct timer8_priv {scalar_t__ mapbase; TYPE_1__ ced; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMFA ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ _8TCR ; 
 scalar_t__ _8TCSR ; 
 int /*<<< orphan*/  bclr (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ clockevent_state_oneshot (TYPE_1__*) ; 
 int /*<<< orphan*/  iowrite16be (int,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static irqreturn_t timer8_interrupt(int irq, void *dev_id)
{
	struct timer8_priv *p = dev_id;

	if (clockevent_state_oneshot(&p->ced))
		iowrite16be(0x0000, p->mapbase + _8TCR);

	p->ced.event_handler(&p->ced);

	bclr(CMFA, p->mapbase + _8TCSR);

	return IRQ_HANDLED;
}