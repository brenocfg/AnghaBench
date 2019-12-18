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
struct mlx5_wqe_srq_next_seg {int /*<<< orphan*/  next_wqe_index; } ;
struct mlx5_srq {int tail; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct mlx5_wqe_srq_next_seg* get_wqe (struct mlx5_srq*,int) ; 
 int /*<<< orphan*/  htobe16 (int) ; 
 int /*<<< orphan*/  mlx5_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_spin_unlock (int /*<<< orphan*/ *) ; 

void mlx5_free_srq_wqe(struct mlx5_srq *srq, int ind)
{
	struct mlx5_wqe_srq_next_seg *next;

	mlx5_spin_lock(&srq->lock);

	next = get_wqe(srq, srq->tail);
	next->next_wqe_index = htobe16(ind);
	srq->tail = ind;

	mlx5_spin_unlock(&srq->lock);
}