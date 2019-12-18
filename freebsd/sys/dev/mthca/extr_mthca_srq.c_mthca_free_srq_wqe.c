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
typedef  int u32 ;
struct mthca_srq {int wqe_shift; int last_free; int /*<<< orphan*/  lock; } ;
struct mthca_next_seg {int /*<<< orphan*/  nda_op; } ;

/* Variables and functions */
 struct mthca_next_seg* get_wqe (struct mthca_srq*,int) ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int* wqe_to_link (struct mthca_next_seg*) ; 

void mthca_free_srq_wqe(struct mthca_srq *srq, u32 wqe_addr)
{
	int ind;
	struct mthca_next_seg *last_free;

	ind = wqe_addr >> srq->wqe_shift;

	spin_lock(&srq->lock);

	last_free = get_wqe(srq, srq->last_free);
	*wqe_to_link(last_free) = ind;
	last_free->nda_op = htonl((ind << srq->wqe_shift) | 1);
	*wqe_to_link(get_wqe(srq, ind)) = -1;
	srq->last_free = ind;

	spin_unlock(&srq->lock);
}