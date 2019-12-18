#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
struct TYPE_7__ {size_t curbytes; size_t accumbytes; int /*<<< orphan*/  accumobjs; int /*<<< orphan*/  curobjs; } ;
struct TYPE_8__ {int prepared; TYPE_1__* tdata; TYPE_2__ cnts; } ;
typedef  TYPE_3__ prof_tctx_t ;
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ opt_prof_accum ; 
 int /*<<< orphan*/  prof_tctx_set (int /*<<< orphan*/ *,void const*,size_t,int /*<<< orphan*/ *,TYPE_3__*) ; 

void
prof_malloc_sample_object(tsdn_t *tsdn, const void *ptr, size_t usize,
    prof_tctx_t *tctx) {
	prof_tctx_set(tsdn, ptr, usize, NULL, tctx);

	malloc_mutex_lock(tsdn, tctx->tdata->lock);
	tctx->cnts.curobjs++;
	tctx->cnts.curbytes += usize;
	if (opt_prof_accum) {
		tctx->cnts.accumobjs++;
		tctx->cnts.accumbytes += usize;
	}
	tctx->prepared = false;
	malloc_mutex_unlock(tsdn, tctx->tdata->lock);
}