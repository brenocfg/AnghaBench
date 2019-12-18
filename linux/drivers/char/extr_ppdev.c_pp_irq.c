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
struct pp_struct {int /*<<< orphan*/  irq_wait; int /*<<< orphan*/  irqc; scalar_t__ irqresponse; int /*<<< orphan*/  irqctl; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parport_write_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pp_irq(void *private)
{
	struct pp_struct *pp = private;

	if (pp->irqresponse) {
		parport_write_control(pp->pdev->port, pp->irqctl);
		pp->irqresponse = 0;
	}

	atomic_inc(&pp->irqc);
	wake_up_interruptible(&pp->irq_wait);
}