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
struct mlx4_qp {int dummy; } ;
struct mlx4_cq {int /*<<< orphan*/  lock; } ;
struct ibv_wc {int dummy; } ;
struct ibv_cq {int dummy; } ;

/* Variables and functions */
 int CQ_OK ; 
 int CQ_POLL_ERR ; 
 int mlx4_poll_one (struct mlx4_cq*,struct mlx4_qp**,struct ibv_wc*) ; 
 int /*<<< orphan*/  mlx4_update_cons_index (struct mlx4_cq*) ; 
 int /*<<< orphan*/  pthread_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_spin_unlock (int /*<<< orphan*/ *) ; 
 struct mlx4_cq* to_mcq (struct ibv_cq*) ; 

int mlx4_poll_cq(struct ibv_cq *ibcq, int ne, struct ibv_wc *wc)
{
	struct mlx4_cq *cq = to_mcq(ibcq);
	struct mlx4_qp *qp = NULL;
	int npolled;
	int err = CQ_OK;

	pthread_spin_lock(&cq->lock);

	for (npolled = 0; npolled < ne; ++npolled) {
		err = mlx4_poll_one(cq, &qp, wc + npolled);
		if (err != CQ_OK)
			break;
	}

	if (npolled || err == CQ_POLL_ERR)
		mlx4_update_cons_index(cq);

	pthread_spin_unlock(&cq->lock);

	return err == CQ_POLL_ERR ? err : npolled;
}