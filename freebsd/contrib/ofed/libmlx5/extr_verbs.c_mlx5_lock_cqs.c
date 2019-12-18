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
struct mlx5_cq {scalar_t__ cqn; int /*<<< orphan*/  lock; } ;
struct ibv_qp {int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_spin_lock (int /*<<< orphan*/ *) ; 
 struct mlx5_cq* to_mcq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx5_lock_cqs(struct ibv_qp *qp)
{
	struct mlx5_cq *send_cq = to_mcq(qp->send_cq);
	struct mlx5_cq *recv_cq = to_mcq(qp->recv_cq);

	if (send_cq && recv_cq) {
		if (send_cq == recv_cq) {
			mlx5_spin_lock(&send_cq->lock);
		} else if (send_cq->cqn < recv_cq->cqn) {
			mlx5_spin_lock(&send_cq->lock);
			mlx5_spin_lock(&recv_cq->lock);
		} else {
			mlx5_spin_lock(&recv_cq->lock);
			mlx5_spin_lock(&send_cq->lock);
		}
	} else if (send_cq) {
		mlx5_spin_lock(&send_cq->lock);
	} else if (recv_cq) {
		mlx5_spin_lock(&recv_cq->lock);
	}
}