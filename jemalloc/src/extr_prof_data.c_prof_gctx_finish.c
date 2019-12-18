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
typedef  int /*<<< orphan*/  prof_tdata_t ;
typedef  int /*<<< orphan*/  prof_tctx_t ;
typedef  int /*<<< orphan*/  prof_gctx_tree_t ;
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  nlimbo; int /*<<< orphan*/  tctxs; } ;
typedef  TYPE_1__ prof_gctx_t ;

/* Variables and functions */
 TYPE_1__* gctx_tree_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gctx_tree_remove (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  idalloctm (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  malloc_mutex_lock (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ prof_gctx_should_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  prof_gctx_try_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prof_tctx_finish_iter ; 
 int /*<<< orphan*/ * prof_tdata_get (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * tctx_tree_iter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/ * tctx_tree_next (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tctx_tree_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ tsd_tsdn (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
prof_gctx_finish(tsd_t *tsd, prof_gctx_tree_t *gctxs) {
	prof_tdata_t *tdata = prof_tdata_get(tsd, false);
	prof_gctx_t *gctx;

	/*
	 * Standard tree iteration won't work here, because as soon as we
	 * decrement gctx->nlimbo and unlock gctx, another thread can
	 * concurrently destroy it, which will corrupt the tree.  Therefore,
	 * tear down the tree one node at a time during iteration.
	 */
	while ((gctx = gctx_tree_first(gctxs)) != NULL) {
		gctx_tree_remove(gctxs, gctx);
		malloc_mutex_lock(tsd_tsdn(tsd), gctx->lock);
		{
			prof_tctx_t *next;

			next = NULL;
			do {
				prof_tctx_t *to_destroy =
				    tctx_tree_iter(&gctx->tctxs, next,
				    prof_tctx_finish_iter,
				    (void *)tsd_tsdn(tsd));
				if (to_destroy != NULL) {
					next = tctx_tree_next(&gctx->tctxs,
					    to_destroy);
					tctx_tree_remove(&gctx->tctxs,
					    to_destroy);
					idalloctm(tsd_tsdn(tsd), to_destroy,
					    NULL, NULL, true, true);
				} else {
					next = NULL;
				}
			} while (next != NULL);
		}
		gctx->nlimbo--;
		if (prof_gctx_should_destroy(gctx)) {
			gctx->nlimbo++;
			malloc_mutex_unlock(tsd_tsdn(tsd), gctx->lock);
			prof_gctx_try_destroy(tsd, tdata, gctx, tdata);
		} else {
			malloc_mutex_unlock(tsd_tsdn(tsd), gctx->lock);
		}
	}
}