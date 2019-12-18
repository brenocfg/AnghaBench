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
struct request_queue {int /*<<< orphan*/  id; int /*<<< orphan*/  queue_lock; } ;
struct io_cq {struct request_queue* q; } ;
struct io_context {int /*<<< orphan*/  icq_hint; int /*<<< orphan*/  icq_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 struct io_cq* radix_tree_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct io_cq*) ; 
 struct io_cq* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

struct io_cq *ioc_lookup_icq(struct io_context *ioc, struct request_queue *q)
{
	struct io_cq *icq;

	lockdep_assert_held(&q->queue_lock);

	/*
	 * icq's are indexed from @ioc using radix tree and hint pointer,
	 * both of which are protected with RCU.  All removals are done
	 * holding both q and ioc locks, and we're holding q lock - if we
	 * find a icq which points to us, it's guaranteed to be valid.
	 */
	rcu_read_lock();
	icq = rcu_dereference(ioc->icq_hint);
	if (icq && icq->q == q)
		goto out;

	icq = radix_tree_lookup(&ioc->icq_tree, q->id);
	if (icq && icq->q == q)
		rcu_assign_pointer(ioc->icq_hint, icq);	/* allowed to race */
	else
		icq = NULL;
out:
	rcu_read_unlock();
	return icq;
}