#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsd_t ;
struct TYPE_6__ {int /*<<< orphan*/  bt2tctx; struct TYPE_6__* thread_name; } ;
typedef  TYPE_1__ prof_tdata_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ckh_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idalloctm (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  malloc_mutex_assert_owner (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prof_tdata_should_destroy_unlocked (TYPE_1__*,int) ; 
 int /*<<< orphan*/  tdata_tree_remove (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  tdatas ; 
 int /*<<< orphan*/  tdatas_mtx ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
prof_tdata_destroy_locked(tsd_t *tsd, prof_tdata_t *tdata,
    bool even_if_attached) {
	malloc_mutex_assert_owner(tsd_tsdn(tsd), &tdatas_mtx);

	tdata_tree_remove(&tdatas, tdata);

	assert(prof_tdata_should_destroy_unlocked(tdata, even_if_attached));

	if (tdata->thread_name != NULL) {
		idalloctm(tsd_tsdn(tsd), tdata->thread_name, NULL, NULL, true,
		    true);
	}
	ckh_delete(tsd, &tdata->bt2tctx);
	idalloctm(tsd_tsdn(tsd), tdata, NULL, NULL, true, true);
}