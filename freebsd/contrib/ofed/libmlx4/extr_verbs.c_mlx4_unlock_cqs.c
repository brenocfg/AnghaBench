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
struct mlx4_cq {scalar_t__ cqn; int /*<<< orphan*/  lock; } ;
struct ibv_qp {int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; } ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_spin_unlock (int /*<<< orphan*/ *) ; 
 struct mlx4_cq* to_mcq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx4_unlock_cqs(struct ibv_qp *qp)
{
	struct mlx4_cq *send_cq = to_mcq(qp->send_cq);
	struct mlx4_cq *recv_cq = to_mcq(qp->recv_cq);


	if (!qp->send_cq || !qp->recv_cq) {
		if (qp->send_cq)
			pthread_spin_unlock(&send_cq->lock);
		else if (qp->recv_cq)
			pthread_spin_unlock(&recv_cq->lock);
	} else if (send_cq == recv_cq) {
		pthread_spin_unlock(&send_cq->lock);
	} else if (send_cq->cqn < recv_cq->cqn) {
		pthread_spin_unlock(&recv_cq->lock);
		pthread_spin_unlock(&send_cq->lock);
	} else {
		pthread_spin_unlock(&send_cq->lock);
		pthread_spin_unlock(&recv_cq->lock);
	}
}