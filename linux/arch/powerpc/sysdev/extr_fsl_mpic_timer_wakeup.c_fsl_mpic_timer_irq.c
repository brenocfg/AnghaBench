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
struct fsl_mpic_timer_wakeup {scalar_t__ timer; int /*<<< orphan*/  free_work; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t fsl_mpic_timer_irq(int irq, void *dev_id)
{
	struct fsl_mpic_timer_wakeup *wakeup = dev_id;

	schedule_work(&wakeup->free_work);

	return wakeup->timer ? IRQ_HANDLED : IRQ_NONE;
}