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
struct mlx4_wq {unsigned int head; unsigned int tail; unsigned int max_post; } ;
struct mlx4_cq {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wq_overflow(struct mlx4_wq *wq, int nreq, struct mlx4_cq *cq)
{
	unsigned cur;

	cur = wq->head - wq->tail;
	if (cur + nreq < wq->max_post)
		return 0;

	pthread_spin_lock(&cq->lock);
	cur = wq->head - wq->tail;
	pthread_spin_unlock(&cq->lock);

	return cur + nreq >= wq->max_post;
}