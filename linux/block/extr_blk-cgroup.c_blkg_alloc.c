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
struct request_queue {int /*<<< orphan*/  node; } ;
struct blkg_policy_data {int plid; struct blkcg_gq* blkg; } ;
struct blkcg_policy {struct blkg_policy_data* (* pd_alloc_fn ) (int /*<<< orphan*/ ,struct request_queue*,struct blkcg*) ;} ;
struct blkcg_gq {struct blkg_policy_data** pd; struct blkcg* blkcg; int /*<<< orphan*/  async_bio_work; int /*<<< orphan*/  async_bios; int /*<<< orphan*/  async_bio_lock; int /*<<< orphan*/  q_node; struct request_queue* q; int /*<<< orphan*/  stat_ios; int /*<<< orphan*/  stat_bytes; int /*<<< orphan*/  refcnt; } ;
struct blkcg {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int BLKCG_MAX_POLS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_list_init (int /*<<< orphan*/ *) ; 
 struct blkcg_policy** blkcg_policy ; 
 int /*<<< orphan*/  blkcg_policy_enabled (struct request_queue*,struct blkcg_policy*) ; 
 int /*<<< orphan*/  blkg_async_bio_workfn ; 
 int /*<<< orphan*/  blkg_free (struct blkcg_gq*) ; 
 int /*<<< orphan*/  blkg_release ; 
 scalar_t__ blkg_rwstat_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct blkcg_gq* kzalloc_node (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ percpu_ref_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 struct blkg_policy_data* stub1 (int /*<<< orphan*/ ,struct request_queue*,struct blkcg*) ; 

__attribute__((used)) static struct blkcg_gq *blkg_alloc(struct blkcg *blkcg, struct request_queue *q,
				   gfp_t gfp_mask)
{
	struct blkcg_gq *blkg;
	int i;

	/* alloc and init base part */
	blkg = kzalloc_node(sizeof(*blkg), gfp_mask, q->node);
	if (!blkg)
		return NULL;

	if (percpu_ref_init(&blkg->refcnt, blkg_release, 0, gfp_mask))
		goto err_free;

	if (blkg_rwstat_init(&blkg->stat_bytes, gfp_mask) ||
	    blkg_rwstat_init(&blkg->stat_ios, gfp_mask))
		goto err_free;

	blkg->q = q;
	INIT_LIST_HEAD(&blkg->q_node);
	spin_lock_init(&blkg->async_bio_lock);
	bio_list_init(&blkg->async_bios);
	INIT_WORK(&blkg->async_bio_work, blkg_async_bio_workfn);
	blkg->blkcg = blkcg;

	for (i = 0; i < BLKCG_MAX_POLS; i++) {
		struct blkcg_policy *pol = blkcg_policy[i];
		struct blkg_policy_data *pd;

		if (!blkcg_policy_enabled(q, pol))
			continue;

		/* alloc per-policy data and attach it to blkg */
		pd = pol->pd_alloc_fn(gfp_mask, q, blkcg);
		if (!pd)
			goto err_free;

		blkg->pd[i] = pd;
		pd->blkg = blkg;
		pd->plid = i;
	}

	return blkg;

err_free:
	blkg_free(blkg);
	return NULL;
}