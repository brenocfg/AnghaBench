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
struct lio_tq {int /*<<< orphan*/  work; int /*<<< orphan*/ * tq; struct octeon_device* ctxptr; } ;
struct octeon_device {int /*<<< orphan*/  octeon_id; int /*<<< orphan*/  cmd_resp_state; struct lio_tq dma_comp_tq; int /*<<< orphan*/  cmd_resp_wqlock; TYPE_1__* response_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  pending_req_count; int /*<<< orphan*/  lock; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  LIO_DRV_ONLINE ; 
 int LIO_MAX_RESPONSE_LISTS ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  PI_NET ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TIMEOUT_TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  atomic_store_rel_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_dev_err (struct octeon_device*,char*) ; 
 int /*<<< orphan*/  lio_ms_to_ticks (int) ; 
 int /*<<< orphan*/  lio_poll_req_completion ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * taskqueue_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  taskqueue_enqueue_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_start_threads (int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_thread_enqueue ; 

int
lio_setup_response_list(struct octeon_device *oct)
{
	struct lio_tq	*ctq;
	int		i, ret = 0;

	for (i = 0; i < LIO_MAX_RESPONSE_LISTS; i++) {
		STAILQ_INIT(&oct->response_list[i].head);
		mtx_init(&oct->response_list[i].lock, "response_list_lock",
			 NULL, MTX_DEF);
		atomic_store_rel_int(&oct->response_list[i].pending_req_count,
				     0);
	}
	mtx_init(&oct->cmd_resp_wqlock, "cmd_resp_wqlock", NULL, MTX_DEF);

	ctq = &oct->dma_comp_tq;
	ctq->tq = taskqueue_create("lio_dma_comp", M_WAITOK,
				   taskqueue_thread_enqueue, &ctq->tq);
	if (ctq->tq == NULL) {
		lio_dev_err(oct, "failed to create wq thread\n");
		return (-ENOMEM);
	}

	TIMEOUT_TASK_INIT(ctq->tq, &ctq->work, 0, lio_poll_req_completion,
			  (void *)ctq);
	ctq->ctxptr = oct;

	oct->cmd_resp_state = LIO_DRV_ONLINE;
	taskqueue_start_threads(&ctq->tq, 1, PI_NET, "lio%d_dma_comp",
				oct->octeon_id);
	taskqueue_enqueue_timeout(ctq->tq, &ctq->work, lio_ms_to_ticks(50));

	return (ret);
}