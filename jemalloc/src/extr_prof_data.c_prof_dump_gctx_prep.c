#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  prof_gctx_tree_t ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  cnt_summed; int /*<<< orphan*/  nlimbo; } ;
typedef  TYPE_1__ prof_gctx_t ;
typedef  int /*<<< orphan*/  prof_cnt_t ;

/* Variables and functions */
 int /*<<< orphan*/  cassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_prof ; 
 int /*<<< orphan*/  gctx_tree_insert (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
prof_dump_gctx_prep(tsdn_t *tsdn, prof_gctx_t *gctx, prof_gctx_tree_t *gctxs) {
	cassert(config_prof);

	malloc_mutex_lock(tsdn, gctx->lock);

	/*
	 * Increment nlimbo so that gctx won't go away before dump.
	 * Additionally, link gctx into the dump list so that it is included in
	 * prof_dump()'s second pass.
	 */
	gctx->nlimbo++;
	gctx_tree_insert(gctxs, gctx);

	memset(&gctx->cnt_summed, 0, sizeof(prof_cnt_t));

	malloc_mutex_unlock(tsdn, gctx->lock);
}