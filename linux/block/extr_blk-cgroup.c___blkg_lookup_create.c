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
struct request_queue {struct blkcg_gq* root_blkg; int /*<<< orphan*/  queue_lock; } ;
struct blkcg_gq {int dummy; } ;
struct blkcg {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct blkcg_gq*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct blkcg_gq* __blkg_lookup (struct blkcg*,struct request_queue*,int) ; 
 struct blkcg* blkcg_parent (struct blkcg*) ; 
 struct blkcg_gq* blkg_create (struct blkcg*,struct request_queue*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock_held () ; 

struct blkcg_gq *__blkg_lookup_create(struct blkcg *blkcg,
				      struct request_queue *q)
{
	struct blkcg_gq *blkg;

	WARN_ON_ONCE(!rcu_read_lock_held());
	lockdep_assert_held(&q->queue_lock);

	blkg = __blkg_lookup(blkcg, q, true);
	if (blkg)
		return blkg;

	/*
	 * Create blkgs walking down from blkcg_root to @blkcg, so that all
	 * non-root blkgs have access to their parents.  Returns the closest
	 * blkg to the intended blkg should blkg_create() fail.
	 */
	while (true) {
		struct blkcg *pos = blkcg;
		struct blkcg *parent = blkcg_parent(blkcg);
		struct blkcg_gq *ret_blkg = q->root_blkg;

		while (parent) {
			blkg = __blkg_lookup(parent, q, false);
			if (blkg) {
				/* remember closest blkg */
				ret_blkg = blkg;
				break;
			}
			pos = parent;
			parent = blkcg_parent(parent);
		}

		blkg = blkg_create(pos, q, NULL);
		if (IS_ERR(blkg))
			return ret_blkg;
		if (pos == blkcg)
			return blkg;
	}
}