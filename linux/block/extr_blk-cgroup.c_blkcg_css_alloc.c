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
struct cgroup_subsys_state {int dummy; } ;
struct blkcg_policy_data {int plid; struct blkcg* blkcg; } ;
struct blkcg_policy {int /*<<< orphan*/  (* cpd_free_fn ) (struct blkcg_policy_data*) ;int /*<<< orphan*/  (* cpd_init_fn ) (struct blkcg_policy_data*) ;struct blkcg_policy_data* (* cpd_alloc_fn ) (int /*<<< orphan*/ ) ;} ;
struct blkcg {struct blkcg_policy_data** cpd; struct cgroup_subsys_state css; int /*<<< orphan*/  all_blkcgs_node; int /*<<< orphan*/  cgwb_refcnt; int /*<<< orphan*/  cgwb_list; int /*<<< orphan*/  blkg_list; int /*<<< orphan*/  blkg_tree; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int BLKCG_MAX_POLS ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct cgroup_subsys_state* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GFP_NOWAIT ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_RADIX_TREE (int /*<<< orphan*/ *,int) ; 
 int __GFP_NOWARN ; 
 int /*<<< orphan*/  all_blkcgs ; 
 int /*<<< orphan*/  blkcg_pol_mutex ; 
 struct blkcg_policy** blkcg_policy ; 
 struct blkcg blkcg_root ; 
 int /*<<< orphan*/  kfree (struct blkcg*) ; 
 struct blkcg* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 struct blkcg_policy_data* stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct blkcg_policy_data*) ; 
 int /*<<< orphan*/  stub3 (struct blkcg_policy_data*) ; 

__attribute__((used)) static struct cgroup_subsys_state *
blkcg_css_alloc(struct cgroup_subsys_state *parent_css)
{
	struct blkcg *blkcg;
	struct cgroup_subsys_state *ret;
	int i;

	mutex_lock(&blkcg_pol_mutex);

	if (!parent_css) {
		blkcg = &blkcg_root;
	} else {
		blkcg = kzalloc(sizeof(*blkcg), GFP_KERNEL);
		if (!blkcg) {
			ret = ERR_PTR(-ENOMEM);
			goto unlock;
		}
	}

	for (i = 0; i < BLKCG_MAX_POLS ; i++) {
		struct blkcg_policy *pol = blkcg_policy[i];
		struct blkcg_policy_data *cpd;

		/*
		 * If the policy hasn't been attached yet, wait for it
		 * to be attached before doing anything else. Otherwise,
		 * check if the policy requires any specific per-cgroup
		 * data: if it does, allocate and initialize it.
		 */
		if (!pol || !pol->cpd_alloc_fn)
			continue;

		cpd = pol->cpd_alloc_fn(GFP_KERNEL);
		if (!cpd) {
			ret = ERR_PTR(-ENOMEM);
			goto free_pd_blkcg;
		}
		blkcg->cpd[i] = cpd;
		cpd->blkcg = blkcg;
		cpd->plid = i;
		if (pol->cpd_init_fn)
			pol->cpd_init_fn(cpd);
	}

	spin_lock_init(&blkcg->lock);
	INIT_RADIX_TREE(&blkcg->blkg_tree, GFP_NOWAIT | __GFP_NOWARN);
	INIT_HLIST_HEAD(&blkcg->blkg_list);
#ifdef CONFIG_CGROUP_WRITEBACK
	INIT_LIST_HEAD(&blkcg->cgwb_list);
	refcount_set(&blkcg->cgwb_refcnt, 1);
#endif
	list_add_tail(&blkcg->all_blkcgs_node, &all_blkcgs);

	mutex_unlock(&blkcg_pol_mutex);
	return &blkcg->css;

free_pd_blkcg:
	for (i--; i >= 0; i--)
		if (blkcg->cpd[i])
			blkcg_policy[i]->cpd_free_fn(blkcg->cpd[i]);

	if (blkcg != &blkcg_root)
		kfree(blkcg);
unlock:
	mutex_unlock(&blkcg_pol_mutex);
	return ret;
}