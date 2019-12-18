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
struct TYPE_3__ {int /*<<< orphan*/  sda_tx; int /*<<< orphan*/  sda_sublist_idx; int /*<<< orphan*/  sda_list; } ;
typedef  TYPE_1__ sync_dnodes_arg_t ;
typedef  int /*<<< orphan*/  multilist_sublist_t ;

/* Variables and functions */
 int /*<<< orphan*/  dmu_objset_sync_dnodes (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * multilist_sublist_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  multilist_sublist_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sync_dnodes_task(void *arg)
{
	sync_dnodes_arg_t *sda = arg;

	multilist_sublist_t *ms =
	    multilist_sublist_lock(sda->sda_list, sda->sda_sublist_idx);

	dmu_objset_sync_dnodes(ms, sda->sda_tx);

	multilist_sublist_unlock(ms);

	kmem_free(sda, sizeof (*sda));
}