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
struct mlx4_wqe_srq_next_seg {int /*<<< orphan*/  next_wqe_index; } ;
struct mlx4_srq {int tail; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct mlx4_wqe_srq_next_seg* get_wqe (struct mlx4_srq*,int) ; 
 int /*<<< orphan*/  htobe16 (int) ; 
 int /*<<< orphan*/  pthread_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_spin_unlock (int /*<<< orphan*/ *) ; 

void mlx4_free_srq_wqe(struct mlx4_srq *srq, int ind)
{
	struct mlx4_wqe_srq_next_seg *next;

	pthread_spin_lock(&srq->lock);

	next = get_wqe(srq, srq->tail);
	next->next_wqe_index = htobe16(ind);
	srq->tail = ind;

	pthread_spin_unlock(&srq->lock);
}