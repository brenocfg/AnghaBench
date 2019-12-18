#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
struct TYPE_8__ {scalar_t__ accumbytes; scalar_t__ accumobjs; scalar_t__ curbytes; scalar_t__ curobjs; } ;
struct TYPE_9__ {TYPE_2__ dump_cnts; } ;
typedef  TYPE_3__ prof_tctx_t ;
struct TYPE_7__ {int /*<<< orphan*/  accumbytes; int /*<<< orphan*/  accumobjs; int /*<<< orphan*/  curbytes; int /*<<< orphan*/  curobjs; } ;
struct TYPE_10__ {TYPE_1__ cnt_summed; int /*<<< orphan*/  lock; } ;
typedef  TYPE_4__ prof_gctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  malloc_mutex_assert_owner (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ opt_prof_accum ; 

__attribute__((used)) static void
prof_tctx_merge_gctx(tsdn_t *tsdn, prof_tctx_t *tctx, prof_gctx_t *gctx) {
	malloc_mutex_assert_owner(tsdn, gctx->lock);

	gctx->cnt_summed.curobjs += tctx->dump_cnts.curobjs;
	gctx->cnt_summed.curbytes += tctx->dump_cnts.curbytes;
	if (opt_prof_accum) {
		gctx->cnt_summed.accumobjs += tctx->dump_cnts.accumobjs;
		gctx->cnt_summed.accumbytes += tctx->dump_cnts.accumbytes;
	}
}