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
struct pci_dev {int dummy; } ;
struct nitrox_q_vector {int valid; int /*<<< orphan*/  resp_tasklet; } ;
struct nitrox_device {int num_vecs; struct nitrox_q_vector* qvec; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int,struct nitrox_q_vector*) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nitrox_q_vector*) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (struct pci_dev*) ; 
 int pci_irq_vector (struct pci_dev*,int) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

void nitrox_unregister_interrupts(struct nitrox_device *ndev)
{
	struct pci_dev *pdev = ndev->pdev;
	int i;

	for (i = 0; i < ndev->num_vecs; i++) {
		struct nitrox_q_vector *qvec;
		int vec;

		qvec = ndev->qvec + i;
		if (!qvec->valid)
			continue;

		/* get the vector number */
		vec = pci_irq_vector(pdev, i);
		irq_set_affinity_hint(vec, NULL);
		free_irq(vec, qvec);

		tasklet_disable(&qvec->resp_tasklet);
		tasklet_kill(&qvec->resp_tasklet);
		qvec->valid = false;
	}
	kfree(ndev->qvec);
	ndev->qvec = NULL;
	pci_free_irq_vectors(pdev);
}