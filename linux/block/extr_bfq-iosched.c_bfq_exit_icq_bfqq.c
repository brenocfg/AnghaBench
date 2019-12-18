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
struct bfq_queue {int /*<<< orphan*/ * bic; struct bfq_data* bfqd; } ;
struct bfq_io_cq {int dummy; } ;
struct bfq_data {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfq_exit_bfqq (struct bfq_data*,struct bfq_queue*) ; 
 int /*<<< orphan*/  bic_set_bfqq (struct bfq_io_cq*,int /*<<< orphan*/ *,int) ; 
 struct bfq_queue* bic_to_bfqq (struct bfq_io_cq*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void bfq_exit_icq_bfqq(struct bfq_io_cq *bic, bool is_sync)
{
	struct bfq_queue *bfqq = bic_to_bfqq(bic, is_sync);
	struct bfq_data *bfqd;

	if (bfqq)
		bfqd = bfqq->bfqd; /* NULL if scheduler already exited */

	if (bfqq && bfqd) {
		unsigned long flags;

		spin_lock_irqsave(&bfqd->lock, flags);
		bfqq->bic = NULL;
		bfq_exit_bfqq(bfqd, bfqq);
		bic_set_bfqq(bic, NULL, is_sync);
		spin_unlock_irqrestore(&bfqd->lock, flags);
	}
}