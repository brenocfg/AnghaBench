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
struct TYPE_2__ {int /*<<< orphan*/ * vfdev; int /*<<< orphan*/ * pf2vf_wq; } ;
struct nitrox_device {TYPE_1__ iov; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_pf2vf_mbox_interrupts (struct nitrox_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void nitrox_mbox_cleanup(struct nitrox_device *ndev)
{
	/* disable pf2vf mailbox interrupts */
	disable_pf2vf_mbox_interrupts(ndev);
	/* destroy workqueue */
	if (ndev->iov.pf2vf_wq)
		destroy_workqueue(ndev->iov.pf2vf_wq);

	kfree(ndev->iov.vfdev);
	ndev->iov.pf2vf_wq = NULL;
	ndev->iov.vfdev = NULL;
}