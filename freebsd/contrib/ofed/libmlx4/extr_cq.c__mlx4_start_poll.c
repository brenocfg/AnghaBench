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
struct mlx4_cqe {int dummy; } ;
struct mlx4_cq {int /*<<< orphan*/  lock; int /*<<< orphan*/ * cur_qp; } ;
struct ibv_poll_cq_attr {int /*<<< orphan*/  comp_mask; } ;
struct ibv_cq_ex {int dummy; } ;

/* Variables and functions */
 int CQ_EMPTY ; 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  ibv_cq_ex_to_cq (struct ibv_cq_ex*) ; 
 int mlx4_get_next_cqe (struct mlx4_cq*,struct mlx4_cqe**) ; 
 int mlx4_parse_lazy_cqe (struct mlx4_cq*,struct mlx4_cqe*) ; 
 int /*<<< orphan*/  pthread_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_spin_unlock (int /*<<< orphan*/ *) ; 
 struct mlx4_cq* to_mcq (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int _mlx4_start_poll(struct ibv_cq_ex *ibcq,
				   struct ibv_poll_cq_attr *attr,
				   int lock)
{
	struct mlx4_cq *cq = to_mcq(ibv_cq_ex_to_cq(ibcq));
	struct mlx4_cqe *cqe;
	int err;

	if (unlikely(attr->comp_mask))
		return EINVAL;

	if (lock)
		pthread_spin_lock(&cq->lock);

	cq->cur_qp = NULL;

	err = mlx4_get_next_cqe(cq, &cqe);
	if (err == CQ_EMPTY) {
		if (lock)
			pthread_spin_unlock(&cq->lock);
		return ENOENT;
	}

	err = mlx4_parse_lazy_cqe(cq, cqe);
	if (lock && err)
		pthread_spin_unlock(&cq->lock);

	return err;
}