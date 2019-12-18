#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  next_wqe_index; } ;
struct mlx5e_rx_wqe {TYPE_1__ next; } ;
struct TYPE_7__ {int /*<<< orphan*/  head; } ;
struct mlx5e_rq {scalar_t__ enabled; TYPE_2__ wq; int /*<<< orphan*/  watchdog; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_thread_fence_rel () ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_reset_curcpu (int /*<<< orphan*/ *,int,void*,struct mlx5e_rq*) ; 
 struct mlx5e_rx_wqe* mlx5_wq_ll_get_wqe (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_wq_ll_is_full (TYPE_2__*) ; 
 int /*<<< orphan*/  mlx5_wq_ll_push (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_wq_ll_update_db_record (TYPE_2__*) ; 
 int mlx5e_alloc_rx_wqe (struct mlx5e_rq*,struct mlx5e_rx_wqe*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
mlx5e_post_rx_wqes(struct mlx5e_rq *rq)
{
	if (unlikely(rq->enabled == 0))
		return;

	while (!mlx5_wq_ll_is_full(&rq->wq)) {
		struct mlx5e_rx_wqe *wqe = mlx5_wq_ll_get_wqe(&rq->wq, rq->wq.head);

		if (unlikely(mlx5e_alloc_rx_wqe(rq, wqe, rq->wq.head))) {
			callout_reset_curcpu(&rq->watchdog, 1, (void *)&mlx5e_post_rx_wqes, rq);
			break;
		}
		mlx5_wq_ll_push(&rq->wq, be16_to_cpu(wqe->next.next_wqe_index));
	}

	/* ensure wqes are visible to device before updating doorbell record */
	atomic_thread_fence_rel();

	mlx5_wq_ll_update_db_record(&rq->wq);
}