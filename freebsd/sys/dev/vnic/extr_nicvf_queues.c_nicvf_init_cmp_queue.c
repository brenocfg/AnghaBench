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
struct nicvf {double cq_coalesce_usecs; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;
struct cmp_queue {int idx; int /*<<< orphan*/  cmp_taskq; int /*<<< orphan*/  cmp_task; int /*<<< orphan*/  mtx; int /*<<< orphan*/  rx_br; struct nicvf* nic; int /*<<< orphan*/  thresh; TYPE_1__ dmem; int /*<<< orphan*/  desc; int /*<<< orphan*/  mtx_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMP_QUEUE_CQE_THRESH ; 
 int /*<<< orphan*/  CMP_QUEUE_DESC_SIZE ; 
 int CMP_QUEUE_LEN ; 
 double CMP_QUEUE_TIMER_THRESH ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  NICVF_CQ_BASE_ALIGN_BYTES ; 
 int /*<<< orphan*/  PI_NET ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cmp_queue*) ; 
 int /*<<< orphan*/  buf_ring_alloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nicvf_alloc_q_desc_mem (struct nicvf*,TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nicvf_cmp_task ; 
 scalar_t__ pass1_silicon (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int) ; 
 int /*<<< orphan*/  taskqueue_create_fast (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_start_threads (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  taskqueue_thread_enqueue ; 

__attribute__((used)) static int
nicvf_init_cmp_queue(struct nicvf *nic, struct cmp_queue *cq, int q_len,
    int qidx)
{
	int err;

	/* Initizalize lock */
	snprintf(cq->mtx_name, sizeof(cq->mtx_name), "%s: CQ(%d) lock",
	    device_get_nameunit(nic->dev), qidx);
	mtx_init(&cq->mtx, cq->mtx_name, NULL, MTX_DEF);

	err = nicvf_alloc_q_desc_mem(nic, &cq->dmem, q_len, CMP_QUEUE_DESC_SIZE,
				     NICVF_CQ_BASE_ALIGN_BYTES);

	if (err != 0) {
		device_printf(nic->dev,
		    "Could not allocate DMA memory for CQ\n");
		return (err);
	}

	cq->desc = cq->dmem.base;
	cq->thresh = pass1_silicon(nic->dev) ? 0 : CMP_QUEUE_CQE_THRESH;
	cq->nic = nic;
	cq->idx = qidx;
	nic->cq_coalesce_usecs = (CMP_QUEUE_TIMER_THRESH * 0.05) - 1;

	cq->rx_br = buf_ring_alloc(CMP_QUEUE_LEN * 8, M_DEVBUF, M_WAITOK,
	    &cq->mtx);

	/* Allocate taskqueue */
	TASK_INIT(&cq->cmp_task, 0, nicvf_cmp_task, cq);
	cq->cmp_taskq = taskqueue_create_fast("nicvf_cmp_taskq", M_WAITOK,
	    taskqueue_thread_enqueue, &cq->cmp_taskq);
	taskqueue_start_threads(&cq->cmp_taskq, 1, PI_NET, "%s: cmp_taskq(%d)",
	    device_get_nameunit(nic->dev), qidx);

	return (0);
}