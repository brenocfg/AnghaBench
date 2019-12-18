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
struct sh_tmu_channel {TYPE_1__ ced; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  TCR ; 
 int TCR_TPSC_CLK4 ; 
 int TCR_UNIE ; 
 scalar_t__ clockevent_state_oneshot (TYPE_1__*) ; 
 int /*<<< orphan*/  sh_tmu_write (struct sh_tmu_channel*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static irqreturn_t sh_tmu_interrupt(int irq, void *dev_id)
{
	struct sh_tmu_channel *ch = dev_id;

	/* disable or acknowledge interrupt */
	if (clockevent_state_oneshot(&ch->ced))
		sh_tmu_write(ch, TCR, TCR_TPSC_CLK4);
	else
		sh_tmu_write(ch, TCR, TCR_UNIE | TCR_TPSC_CLK4);

	/* notify clockevent layer */
	ch->ced.event_handler(&ch->ced);
	return IRQ_HANDLED;
}