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
struct pci_dev {int dummy; } ;
struct nitrox_q_vector {int valid; int /*<<< orphan*/  resp_tasklet; } ;
struct TYPE_3__ {int vector; } ;
struct TYPE_4__ {TYPE_1__ msix; } ;
struct nitrox_device {int num_vecs; struct nitrox_q_vector* qvec; TYPE_2__ iov; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int,struct nitrox_q_vector*) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nitrox_q_vector*) ; 
 int /*<<< orphan*/  pci_disable_msix (struct pci_dev*) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

void nitrox_sriov_unregister_interrupts(struct nitrox_device *ndev)
{
	struct pci_dev *pdev = ndev->pdev;
	int i;

	for (i = 0; i < ndev->num_vecs; i++) {
		struct nitrox_q_vector *qvec;
		int vec;

		qvec = ndev->qvec + i;
		if (!qvec->valid)
			continue;

		vec = ndev->iov.msix.vector;
		irq_set_affinity_hint(vec, NULL);
		free_irq(vec, qvec);

		tasklet_disable(&qvec->resp_tasklet);
		tasklet_kill(&qvec->resp_tasklet);
		qvec->valid = false;
	}
	kfree(ndev->qvec);
	ndev->qvec = NULL;
	pci_disable_msix(pdev);
}