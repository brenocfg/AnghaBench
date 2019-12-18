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
struct blkcg_policy {int dummy; } ;
struct blkcg_gq {int dummy; } ;
struct blkcg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EOPNOTSUPP ; 
 struct blkcg_gq* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct blkcg_gq* __blkg_lookup (struct blkcg*,struct request_queue*,int) ; 
 int /*<<< orphan*/  blkcg_policy_enabled (struct request_queue*,struct blkcg_policy const*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock_held () ; 

__attribute__((used)) static struct blkcg_gq *blkg_lookup_check(struct blkcg *blkcg,
					  const struct blkcg_policy *pol,
					  struct request_queue *q)
{
	WARN_ON_ONCE(!rcu_read_lock_held());
	lockdep_assert_held(&q->queue_lock);

	if (!blkcg_policy_enabled(q, pol))
		return ERR_PTR(-EOPNOTSUPP);
	return __blkg_lookup(blkcg, q, true /* update_hint */);
}