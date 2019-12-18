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
struct request_queue {int /*<<< orphan*/  queue_lock; } ;
struct io_context {int dummy; } ;
struct bfq_io_cq {int dummy; } ;
struct bfq_data {int dummy; } ;

/* Variables and functions */
 struct bfq_io_cq* icq_to_bic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioc_lookup_icq (struct io_context*,struct request_queue*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct bfq_io_cq *bfq_bic_lookup(struct bfq_data *bfqd,
					struct io_context *ioc,
					struct request_queue *q)
{
	if (ioc) {
		unsigned long flags;
		struct bfq_io_cq *icq;

		spin_lock_irqsave(&q->queue_lock, flags);
		icq = icq_to_bic(ioc_lookup_icq(ioc, q));
		spin_unlock_irqrestore(&q->queue_lock, flags);

		return icq;
	}

	return NULL;
}