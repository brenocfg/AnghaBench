#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct blkcg_policy {int /*<<< orphan*/  (* pd_offline_fn ) (int /*<<< orphan*/ ) ;} ;
struct blkcg_gq {int online; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  blkcg_node; int /*<<< orphan*/  q_node; TYPE_1__* q; int /*<<< orphan*/  stat_ios; int /*<<< orphan*/  stat_bytes; int /*<<< orphan*/ * pd; struct blkcg_gq* parent; struct blkcg* blkcg; } ;
struct blkcg {int /*<<< orphan*/  blkg_hint; int /*<<< orphan*/  blkg_tree; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; int /*<<< orphan*/  queue_lock; } ;

/* Variables and functions */
 int BLKCG_MAX_POLS ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 struct blkcg_policy** blkcg_policy ; 
 int /*<<< orphan*/  blkg_rwstat_add_aux (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_del_init_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_unhashed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_ref_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radix_tree_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct blkcg_gq* rcu_access_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void blkg_destroy(struct blkcg_gq *blkg)
{
	struct blkcg *blkcg = blkg->blkcg;
	struct blkcg_gq *parent = blkg->parent;
	int i;

	lockdep_assert_held(&blkg->q->queue_lock);
	lockdep_assert_held(&blkcg->lock);

	/* Something wrong if we are trying to remove same group twice */
	WARN_ON_ONCE(list_empty(&blkg->q_node));
	WARN_ON_ONCE(hlist_unhashed(&blkg->blkcg_node));

	for (i = 0; i < BLKCG_MAX_POLS; i++) {
		struct blkcg_policy *pol = blkcg_policy[i];

		if (blkg->pd[i] && pol->pd_offline_fn)
			pol->pd_offline_fn(blkg->pd[i]);
	}

	if (parent) {
		blkg_rwstat_add_aux(&parent->stat_bytes, &blkg->stat_bytes);
		blkg_rwstat_add_aux(&parent->stat_ios, &blkg->stat_ios);
	}

	blkg->online = false;

	radix_tree_delete(&blkcg->blkg_tree, blkg->q->id);
	list_del_init(&blkg->q_node);
	hlist_del_init_rcu(&blkg->blkcg_node);

	/*
	 * Both setting lookup hint to and clearing it from @blkg are done
	 * under queue_lock.  If it's not pointing to @blkg now, it never
	 * will.  Hint assignment itself can race safely.
	 */
	if (rcu_access_pointer(blkcg->blkg_hint) == blkg)
		rcu_assign_pointer(blkcg->blkg_hint, NULL);

	/*
	 * Put the reference taken at the time of creation so that when all
	 * queues are gone, group can be destroyed.
	 */
	percpu_ref_kill(&blkg->refcnt);
}