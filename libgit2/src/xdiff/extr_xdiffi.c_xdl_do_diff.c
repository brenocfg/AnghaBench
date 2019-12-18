#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int flags; } ;
typedef  TYPE_3__ xpparam_t ;
struct TYPE_20__ {int /*<<< orphan*/  rindex; int /*<<< orphan*/  rchg; int /*<<< orphan*/  ha; int /*<<< orphan*/  nreff; } ;
struct TYPE_19__ {int /*<<< orphan*/  rindex; int /*<<< orphan*/  rchg; int /*<<< orphan*/  ha; int /*<<< orphan*/  nreff; } ;
struct TYPE_22__ {TYPE_2__ xdf2; TYPE_1__ xdf1; } ;
typedef  TYPE_4__ xdfenv_t ;
struct TYPE_23__ {scalar_t__ mxcost; int /*<<< orphan*/  heur_min; int /*<<< orphan*/  snake_cnt; } ;
typedef  TYPE_5__ xdalgoenv_t ;
typedef  int /*<<< orphan*/  mmfile_t ;
struct TYPE_24__ {int /*<<< orphan*/  nrec; int /*<<< orphan*/  rindex; int /*<<< orphan*/  rchg; int /*<<< orphan*/  ha; } ;
typedef  TYPE_6__ diffdata_t ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC_ADD (size_t*,size_t,int) ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC_ADD3 (size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC_MULTIPLY (size_t*,size_t,int) ; 
 scalar_t__ XDF_DIFF_ALG (int) ; 
 scalar_t__ XDF_HISTOGRAM_DIFF ; 
 int XDF_NEED_MINIMAL ; 
 scalar_t__ XDF_PATIENCE_DIFF ; 
 int /*<<< orphan*/  XDL_HEUR_MIN_COST ; 
 scalar_t__ XDL_MAX_COST_MIN ; 
 int /*<<< orphan*/  XDL_SNAKE_CNT ; 
 scalar_t__ xdl_bogosqrt (size_t) ; 
 int xdl_do_histogram_diff (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__ const*,TYPE_4__*) ; 
 int xdl_do_patience_diff (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__ const*,TYPE_4__*) ; 
 int /*<<< orphan*/  xdl_free (long*) ; 
 int /*<<< orphan*/  xdl_free_env (TYPE_4__*) ; 
 scalar_t__ xdl_malloc (size_t) ; 
 scalar_t__ xdl_prepare_env (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__ const*,TYPE_4__*) ; 
 scalar_t__ xdl_recs_cmp (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long*,long*,int,TYPE_5__*) ; 

int xdl_do_diff(mmfile_t *mf1, mmfile_t *mf2, xpparam_t const *xpp,
		xdfenv_t *xe) {
	size_t ndiags, allocsize;
	long *kvd, *kvdf, *kvdb;
	xdalgoenv_t xenv;
	diffdata_t dd1, dd2;

	if (XDF_DIFF_ALG(xpp->flags) == XDF_PATIENCE_DIFF)
		return xdl_do_patience_diff(mf1, mf2, xpp, xe);

	if (XDF_DIFF_ALG(xpp->flags) == XDF_HISTOGRAM_DIFF)
		return xdl_do_histogram_diff(mf1, mf2, xpp, xe);

	if (xdl_prepare_env(mf1, mf2, xpp, xe) < 0) {

		return -1;
	}

	/*
	 * Allocate and setup K vectors to be used by the differential algorithm.
	 * One is to store the forward path and one to store the backward path.
	 */
	GIT_ERROR_CHECK_ALLOC_ADD3(&ndiags, xe->xdf1.nreff, xe->xdf2.nreff, 3);
	GIT_ERROR_CHECK_ALLOC_MULTIPLY(&allocsize, ndiags, 2);
	GIT_ERROR_CHECK_ALLOC_ADD(&allocsize, allocsize, 2);
	GIT_ERROR_CHECK_ALLOC_MULTIPLY(&allocsize, allocsize, sizeof(long));

	if (!(kvd = (long *) xdl_malloc(allocsize))) {
		xdl_free_env(xe);
		return -1;
	}
	kvdf = kvd;
	kvdb = kvdf + ndiags;
	kvdf += xe->xdf2.nreff + 1;
	kvdb += xe->xdf2.nreff + 1;

	xenv.mxcost = xdl_bogosqrt(ndiags);
	if (xenv.mxcost < XDL_MAX_COST_MIN)
		xenv.mxcost = XDL_MAX_COST_MIN;
	xenv.snake_cnt = XDL_SNAKE_CNT;
	xenv.heur_min = XDL_HEUR_MIN_COST;

	dd1.nrec = xe->xdf1.nreff;
	dd1.ha = xe->xdf1.ha;
	dd1.rchg = xe->xdf1.rchg;
	dd1.rindex = xe->xdf1.rindex;
	dd2.nrec = xe->xdf2.nreff;
	dd2.ha = xe->xdf2.ha;
	dd2.rchg = xe->xdf2.rchg;
	dd2.rindex = xe->xdf2.rindex;

	if (xdl_recs_cmp(&dd1, 0, dd1.nrec, &dd2, 0, dd2.nrec,
			 kvdf, kvdb, (xpp->flags & XDF_NEED_MINIMAL) != 0, &xenv) < 0) {

		xdl_free(kvd);
		xdl_free_env(xe);
		return -1;
	}

	xdl_free(kvd);

	return 0;
}