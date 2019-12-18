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
struct qm_dma {int /*<<< orphan*/  dma; scalar_t__ va; int /*<<< orphan*/  size; } ;
struct hisi_qp {size_t qp_id; struct qm_dma qdma; struct hisi_qm* qm; } ;
struct hisi_qm {int /*<<< orphan*/  qps_lock; int /*<<< orphan*/  qp_bitmap; int /*<<< orphan*/ ** qp_array; scalar_t__ use_dma_api; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct hisi_qp*) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

void hisi_qm_release_qp(struct hisi_qp *qp)
{
	struct hisi_qm *qm = qp->qm;
	struct qm_dma *qdma = &qp->qdma;
	struct device *dev = &qm->pdev->dev;

	if (qm->use_dma_api && qdma->va)
		dma_free_coherent(dev, qdma->size, qdma->va, qdma->dma);

	write_lock(&qm->qps_lock);
	qm->qp_array[qp->qp_id] = NULL;
	clear_bit(qp->qp_id, qm->qp_bitmap);
	write_unlock(&qm->qps_lock);

	kfree(qp);
}