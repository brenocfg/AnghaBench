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
struct nitrox_vfdev {int vfno; } ;
struct TYPE_2__ {int num_vfs; struct nitrox_vfdev* vfdev; int /*<<< orphan*/  pf2vf_wq; } ;
struct nitrox_device {TYPE_1__ iov; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_pf2vf_mbox_interrupts (struct nitrox_device*) ; 
 struct nitrox_vfdev* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nitrox_vfdev*) ; 

int nitrox_mbox_init(struct nitrox_device *ndev)
{
	struct nitrox_vfdev *vfdev;
	int i;

	ndev->iov.vfdev = kcalloc(ndev->iov.num_vfs,
				  sizeof(struct nitrox_vfdev), GFP_KERNEL);
	if (!ndev->iov.vfdev)
		return -ENOMEM;

	for (i = 0; i < ndev->iov.num_vfs; i++) {
		vfdev = ndev->iov.vfdev + i;
		vfdev->vfno = i;
	}

	/* allocate pf2vf response workqueue */
	ndev->iov.pf2vf_wq = alloc_workqueue("nitrox_pf2vf", 0, 0);
	if (!ndev->iov.pf2vf_wq) {
		kfree(ndev->iov.vfdev);
		return -ENOMEM;
	}
	/* enable pf2vf mailbox interrupts */
	enable_pf2vf_mbox_interrupts(ndev);

	return 0;
}