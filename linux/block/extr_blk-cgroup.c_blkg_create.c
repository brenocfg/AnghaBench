#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int /*<<< orphan*/  blkg_list; int /*<<< orphan*/  id; int /*<<< orphan*/  backing_dev_info; int /*<<< orphan*/  queue_lock; } ;
struct blkcg_policy {int /*<<< orphan*/  (* pd_online_fn ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* pd_init_fn ) (int /*<<< orphan*/ ) ;} ;
struct blkcg_gq {int online; int /*<<< orphan*/ * pd; int /*<<< orphan*/  q_node; int /*<<< orphan*/  blkcg_node; int /*<<< orphan*/  parent; struct bdi_writeback_congested* wb_congested; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
struct blkcg {TYPE_1__ css; int /*<<< orphan*/  lock; int /*<<< orphan*/  blkg_list; int /*<<< orphan*/  blkg_tree; } ;
struct bdi_writeback_congested {int dummy; } ;

/* Variables and functions */
 int BLKCG_MAX_POLS ; 
 int ENODEV ; 
 int ENOMEM ; 
 struct blkcg_gq* ERR_PTR (int) ; 
 int GFP_NOWAIT ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int __GFP_NOWARN ; 
 int /*<<< orphan*/  __blkg_lookup (scalar_t__,struct request_queue*,int) ; 
 scalar_t__ blk_queue_dying (struct request_queue*) ; 
 scalar_t__ blkcg_parent (struct blkcg*) ; 
 struct blkcg_policy** blkcg_policy ; 
 struct blkcg_gq* blkg_alloc (struct blkcg*,struct request_queue*,int) ; 
 int /*<<< orphan*/  blkg_free (struct blkcg_gq*) ; 
 int /*<<< orphan*/  blkg_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blkg_put (struct blkcg_gq*) ; 
 int /*<<< orphan*/  css_put (TYPE_1__*) ; 
 int /*<<< orphan*/  css_tryget_online (TYPE_1__*) ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int radix_tree_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct blkcg_gq*) ; 
 int /*<<< orphan*/  rcu_read_lock_held () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 struct bdi_writeback_congested* wb_congested_get_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wb_congested_put (struct bdi_writeback_congested*) ; 

__attribute__((used)) static struct blkcg_gq *blkg_create(struct blkcg *blkcg,
				    struct request_queue *q,
				    struct blkcg_gq *new_blkg)
{
	struct blkcg_gq *blkg;
	struct bdi_writeback_congested *wb_congested;
	int i, ret;

	WARN_ON_ONCE(!rcu_read_lock_held());
	lockdep_assert_held(&q->queue_lock);

	/* request_queue is dying, do not create/recreate a blkg */
	if (blk_queue_dying(q)) {
		ret = -ENODEV;
		goto err_free_blkg;
	}

	/* blkg holds a reference to blkcg */
	if (!css_tryget_online(&blkcg->css)) {
		ret = -ENODEV;
		goto err_free_blkg;
	}

	wb_congested = wb_congested_get_create(q->backing_dev_info,
					       blkcg->css.id,
					       GFP_NOWAIT | __GFP_NOWARN);
	if (!wb_congested) {
		ret = -ENOMEM;
		goto err_put_css;
	}

	/* allocate */
	if (!new_blkg) {
		new_blkg = blkg_alloc(blkcg, q, GFP_NOWAIT | __GFP_NOWARN);
		if (unlikely(!new_blkg)) {
			ret = -ENOMEM;
			goto err_put_congested;
		}
	}
	blkg = new_blkg;
	blkg->wb_congested = wb_congested;

	/* link parent */
	if (blkcg_parent(blkcg)) {
		blkg->parent = __blkg_lookup(blkcg_parent(blkcg), q, false);
		if (WARN_ON_ONCE(!blkg->parent)) {
			ret = -ENODEV;
			goto err_put_congested;
		}
		blkg_get(blkg->parent);
	}

	/* invoke per-policy init */
	for (i = 0; i < BLKCG_MAX_POLS; i++) {
		struct blkcg_policy *pol = blkcg_policy[i];

		if (blkg->pd[i] && pol->pd_init_fn)
			pol->pd_init_fn(blkg->pd[i]);
	}

	/* insert */
	spin_lock(&blkcg->lock);
	ret = radix_tree_insert(&blkcg->blkg_tree, q->id, blkg);
	if (likely(!ret)) {
		hlist_add_head_rcu(&blkg->blkcg_node, &blkcg->blkg_list);
		list_add(&blkg->q_node, &q->blkg_list);

		for (i = 0; i < BLKCG_MAX_POLS; i++) {
			struct blkcg_policy *pol = blkcg_policy[i];

			if (blkg->pd[i] && pol->pd_online_fn)
				pol->pd_online_fn(blkg->pd[i]);
		}
	}
	blkg->online = true;
	spin_unlock(&blkcg->lock);

	if (!ret)
		return blkg;

	/* @blkg failed fully initialized, use the usual release path */
	blkg_put(blkg);
	return ERR_PTR(ret);

err_put_congested:
	wb_congested_put(wb_congested);
err_put_css:
	css_put(&blkcg->css);
err_free_blkg:
	blkg_free(new_blkg);
	return ERR_PTR(ret);
}