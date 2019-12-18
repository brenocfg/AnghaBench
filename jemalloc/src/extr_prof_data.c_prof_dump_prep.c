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
typedef  int /*<<< orphan*/  tsd_t ;
struct prof_tdata_merge_iter_arg_s {int /*<<< orphan*/  cnt_all; void* tsdn; } ;
struct prof_gctx_merge_iter_arg_s {scalar_t__ leak_ngctx; void* tsdn; } ;
typedef  int /*<<< orphan*/  prof_tdata_t ;
typedef  int /*<<< orphan*/  prof_gctx_tree_t ;
typedef  int /*<<< orphan*/  prof_gctx_t ;
typedef  int /*<<< orphan*/  prof_cnt_t ;

/* Variables and functions */
 int /*<<< orphan*/  bt2gctx ; 
 int /*<<< orphan*/  ckh_iter (int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  gctx_tree_iter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  gctx_tree_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_lock (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  prof_dump_gctx_prep (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prof_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prof_gctx_merge_iter ; 
 int /*<<< orphan*/  prof_leave (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prof_tdata_merge_iter ; 
 int /*<<< orphan*/  tdata_tree_iter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  tdatas ; 
 int /*<<< orphan*/  tdatas_mtx ; 
 void* tsd_tsdn (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
prof_dump_prep(tsd_t *tsd, prof_tdata_t *tdata,
    struct prof_tdata_merge_iter_arg_s *prof_tdata_merge_iter_arg,
    struct prof_gctx_merge_iter_arg_s *prof_gctx_merge_iter_arg,
    prof_gctx_tree_t *gctxs) {
	size_t tabind;
	union {
		prof_gctx_t	*p;
		void		*v;
	} gctx;

	prof_enter(tsd, tdata);

	/*
	 * Put gctx's in limbo and clear their counters in preparation for
	 * summing.
	 */
	gctx_tree_new(gctxs);
	for (tabind = 0; !ckh_iter(&bt2gctx, &tabind, NULL, &gctx.v);) {
		prof_dump_gctx_prep(tsd_tsdn(tsd), gctx.p, gctxs);
	}

	/*
	 * Iterate over tdatas, and for the non-expired ones snapshot their tctx
	 * stats and merge them into the associated gctx's.
	 */
	prof_tdata_merge_iter_arg->tsdn = tsd_tsdn(tsd);
	memset(&prof_tdata_merge_iter_arg->cnt_all, 0, sizeof(prof_cnt_t));
	malloc_mutex_lock(tsd_tsdn(tsd), &tdatas_mtx);
	tdata_tree_iter(&tdatas, NULL, prof_tdata_merge_iter,
	    (void *)prof_tdata_merge_iter_arg);
	malloc_mutex_unlock(tsd_tsdn(tsd), &tdatas_mtx);

	/* Merge tctx stats into gctx's. */
	prof_gctx_merge_iter_arg->tsdn = tsd_tsdn(tsd);
	prof_gctx_merge_iter_arg->leak_ngctx = 0;
	gctx_tree_iter(gctxs, NULL, prof_gctx_merge_iter,
	    (void *)prof_gctx_merge_iter_arg);

	prof_leave(tsd, tdata);
}