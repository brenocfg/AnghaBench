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
struct blkcg_gq {int dummy; } ;
struct blkcg {int dummy; } ;

/* Variables and functions */
 struct blkcg_gq* __blkg_lookup_create (struct blkcg*,struct request_queue*) ; 
 struct blkcg_gq* blkg_lookup (struct blkcg*,struct request_queue*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

struct blkcg_gq *blkg_lookup_create(struct blkcg *blkcg,
				    struct request_queue *q)
{
	struct blkcg_gq *blkg = blkg_lookup(blkcg, q);

	if (unlikely(!blkg)) {
		unsigned long flags;

		spin_lock_irqsave(&q->queue_lock, flags);
		blkg = __blkg_lookup_create(blkcg, q);
		spin_unlock_irqrestore(&q->queue_lock, flags);
	}

	return blkg;
}