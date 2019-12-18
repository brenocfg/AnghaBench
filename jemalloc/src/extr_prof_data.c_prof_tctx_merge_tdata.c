#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
struct TYPE_11__ {int /*<<< orphan*/  accumbytes; int /*<<< orphan*/  accumobjs; int /*<<< orphan*/  curbytes; int /*<<< orphan*/  curobjs; } ;
struct TYPE_12__ {TYPE_3__ cnt_summed; } ;
typedef  TYPE_4__ prof_tdata_t ;
struct TYPE_14__ {int /*<<< orphan*/  accumbytes; int /*<<< orphan*/  accumobjs; int /*<<< orphan*/  curbytes; int /*<<< orphan*/  curobjs; } ;
struct TYPE_13__ {int state; TYPE_8__ dump_cnts; int /*<<< orphan*/  cnts; TYPE_2__* gctx; TYPE_1__* tdata; } ;
typedef  TYPE_5__ prof_tctx_t ;
typedef  int /*<<< orphan*/  prof_cnt_t ;
struct TYPE_10__ {int /*<<< orphan*/  lock; } ;
struct TYPE_9__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  malloc_mutex_assert_owner (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_8__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  not_reached () ; 
 int /*<<< orphan*/  opt_prof_accum ; 
#define  prof_tctx_state_dumping 131 
#define  prof_tctx_state_initializing 130 
#define  prof_tctx_state_nominal 129 
#define  prof_tctx_state_purgatory 128 

__attribute__((used)) static void
prof_tctx_merge_tdata(tsdn_t *tsdn, prof_tctx_t *tctx, prof_tdata_t *tdata) {
	malloc_mutex_assert_owner(tsdn, tctx->tdata->lock);

	malloc_mutex_lock(tsdn, tctx->gctx->lock);

	switch (tctx->state) {
	case prof_tctx_state_initializing:
		malloc_mutex_unlock(tsdn, tctx->gctx->lock);
		return;
	case prof_tctx_state_nominal:
		tctx->state = prof_tctx_state_dumping;
		malloc_mutex_unlock(tsdn, tctx->gctx->lock);

		memcpy(&tctx->dump_cnts, &tctx->cnts, sizeof(prof_cnt_t));

		tdata->cnt_summed.curobjs += tctx->dump_cnts.curobjs;
		tdata->cnt_summed.curbytes += tctx->dump_cnts.curbytes;
		if (opt_prof_accum) {
			tdata->cnt_summed.accumobjs +=
			    tctx->dump_cnts.accumobjs;
			tdata->cnt_summed.accumbytes +=
			    tctx->dump_cnts.accumbytes;
		}
		break;
	case prof_tctx_state_dumping:
	case prof_tctx_state_purgatory:
		not_reached();
	}
}