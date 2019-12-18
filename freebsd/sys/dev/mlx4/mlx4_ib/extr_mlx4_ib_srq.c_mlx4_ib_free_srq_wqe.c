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
struct mlx4_ib_srq {int tail; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 struct mlx4_wqe_srq_next_seg* get_wqe (struct mlx4_ib_srq*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void mlx4_ib_free_srq_wqe(struct mlx4_ib_srq *srq, int wqe_index)
{
	struct mlx4_wqe_srq_next_seg *next;

	/* always called with interrupts disabled. */
	spin_lock(&srq->lock);

	next = get_wqe(srq, srq->tail);
	next->next_wqe_index = cpu_to_be16(wqe_index);
	srq->tail = wqe_index;

	spin_unlock(&srq->lock);
}