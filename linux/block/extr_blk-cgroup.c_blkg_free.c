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
struct blkcg_gq {int /*<<< orphan*/  refcnt; int /*<<< orphan*/  stat_bytes; int /*<<< orphan*/  stat_ios; scalar_t__* pd; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* pd_free_fn ) (scalar_t__) ;} ;

/* Variables and functions */
 int BLKCG_MAX_POLS ; 
 TYPE_1__** blkcg_policy ; 
 int /*<<< orphan*/  blkg_rwstat_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct blkcg_gq*) ; 
 int /*<<< orphan*/  percpu_ref_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

__attribute__((used)) static void blkg_free(struct blkcg_gq *blkg)
{
	int i;

	if (!blkg)
		return;

	for (i = 0; i < BLKCG_MAX_POLS; i++)
		if (blkg->pd[i])
			blkcg_policy[i]->pd_free_fn(blkg->pd[i]);

	blkg_rwstat_exit(&blkg->stat_ios);
	blkg_rwstat_exit(&blkg->stat_bytes);
	percpu_ref_exit(&blkg->refcnt);
	kfree(blkg);
}