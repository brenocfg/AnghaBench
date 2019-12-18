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
typedef  int /*<<< orphan*/  u8 ;
struct qm_cqe {int dummy; } ;
struct TYPE_4__ {int size; int /*<<< orphan*/  dma; int /*<<< orphan*/  va; } ;
struct hisi_qp {int qp_id; TYPE_2__ qdma; int /*<<< orphan*/  wq; int /*<<< orphan*/  work; int /*<<< orphan*/  alg_type; struct hisi_qm* qm; } ;
struct hisi_qm {int qp_num; int sqe_size; int /*<<< orphan*/  qps_lock; int /*<<< orphan*/  qp_bitmap; struct hisi_qp** qp_array; scalar_t__ use_dma_api; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EFAULT ; 
 int ENOMEM ; 
 struct hisi_qp* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int QM_Q_DEPTH ; 
 int WQ_CPU_INTENSIVE ; 
 int WQ_HIGHPRI ; 
 int WQ_MEM_RECLAIM ; 
 int WQ_UNBOUND ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dma_alloc_coherent (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct hisi_qp*) ; 
 struct hisi_qp* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qm_qp_work_func ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

struct hisi_qp *hisi_qm_create_qp(struct hisi_qm *qm, u8 alg_type)
{
	struct device *dev = &qm->pdev->dev;
	struct hisi_qp *qp;
	int qp_id, ret;

	qp = kzalloc(sizeof(*qp), GFP_KERNEL);
	if (!qp)
		return ERR_PTR(-ENOMEM);

	write_lock(&qm->qps_lock);

	qp_id = find_first_zero_bit(qm->qp_bitmap, qm->qp_num);
	if (qp_id >= qm->qp_num) {
		write_unlock(&qm->qps_lock);
		dev_info(&qm->pdev->dev, "QM all queues are busy!\n");
		ret = -EBUSY;
		goto err_free_qp;
	}
	set_bit(qp_id, qm->qp_bitmap);
	qm->qp_array[qp_id] = qp;

	write_unlock(&qm->qps_lock);

	qp->qm = qm;

	if (qm->use_dma_api) {
		qp->qdma.size = qm->sqe_size * QM_Q_DEPTH +
				sizeof(struct qm_cqe) * QM_Q_DEPTH;
		qp->qdma.va = dma_alloc_coherent(dev, qp->qdma.size,
						 &qp->qdma.dma, GFP_KERNEL);
		if (!qp->qdma.va) {
			ret = -ENOMEM;
			goto err_clear_bit;
		}

		dev_dbg(dev, "allocate qp dma buf(va=%pK, dma=%pad, size=%zx)\n",
			qp->qdma.va, &qp->qdma.dma, qp->qdma.size);
	}

	qp->qp_id = qp_id;
	qp->alg_type = alg_type;
	INIT_WORK(&qp->work, qm_qp_work_func);
	qp->wq = alloc_workqueue("hisi_qm", WQ_UNBOUND | WQ_HIGHPRI |
				 WQ_CPU_INTENSIVE | WQ_MEM_RECLAIM, 0);
	if (!qp->wq) {
		ret = -EFAULT;
		goto err_free_qp_mem;
	}

	return qp;

err_free_qp_mem:
	if (qm->use_dma_api)
		dma_free_coherent(dev, qp->qdma.size, qp->qdma.va,
				  qp->qdma.dma);
err_clear_bit:
	write_lock(&qm->qps_lock);
	qm->qp_array[qp_id] = NULL;
	clear_bit(qp_id, qm->qp_bitmap);
	write_unlock(&qm->qps_lock);
err_free_qp:
	kfree(qp);
	return ERR_PTR(ret);
}