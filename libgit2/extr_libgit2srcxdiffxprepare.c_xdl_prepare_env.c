#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ xpparam_t ;
typedef  int /*<<< orphan*/  xdlclassifier_t ;
struct TYPE_7__ {int /*<<< orphan*/  xdf1; int /*<<< orphan*/  xdf2; } ;
typedef  TYPE_2__ xdfenv_t ;
typedef  int /*<<< orphan*/  mmfile_t ;
typedef  int /*<<< orphan*/  cf ;

/* Variables and functions */
 scalar_t__ XDF_DIFF_ALG (int /*<<< orphan*/ ) ; 
 scalar_t__ XDF_HISTOGRAM_DIFF ; 
 scalar_t__ XDF_PATIENCE_DIFF ; 
 long XDL_GUESS_NLINES1 ; 
 long XDL_GUESS_NLINES2 ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xdl_free_classifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdl_free_ctx (int /*<<< orphan*/ *) ; 
 int xdl_guess_lines (int /*<<< orphan*/ *,long) ; 
 scalar_t__ xdl_init_classifier (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 
 scalar_t__ xdl_optimize_ctxs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ xdl_prepare_ctx (int,int /*<<< orphan*/ *,long,TYPE_1__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int xdl_prepare_env(mmfile_t *mf1, mmfile_t *mf2, xpparam_t const *xpp,
		    xdfenv_t *xe) {
	long enl1, enl2, sample;
	xdlclassifier_t cf;

	memset(&cf, 0, sizeof(cf));

	/*
	 * For histogram diff, we can afford a smaller sample size and
	 * thus a poorer estimate of the number of lines, as the hash
	 * table (rhash) won't be filled up/grown. The number of lines
	 * (nrecs) will be updated correctly anyway by
	 * xdl_prepare_ctx().
	 */
	sample = (XDF_DIFF_ALG(xpp->flags) == XDF_HISTOGRAM_DIFF
		  ? XDL_GUESS_NLINES2 : XDL_GUESS_NLINES1);

	enl1 = xdl_guess_lines(mf1, sample) + 1;
	enl2 = xdl_guess_lines(mf2, sample) + 1;

	if (XDF_DIFF_ALG(xpp->flags) != XDF_HISTOGRAM_DIFF &&
	    xdl_init_classifier(&cf, enl1 + enl2 + 1, xpp->flags) < 0)
		return -1;

	if (xdl_prepare_ctx(1, mf1, enl1, xpp, &cf, &xe->xdf1) < 0) {

		xdl_free_classifier(&cf);
		return -1;
	}
	if (xdl_prepare_ctx(2, mf2, enl2, xpp, &cf, &xe->xdf2) < 0) {

		xdl_free_ctx(&xe->xdf1);
		xdl_free_classifier(&cf);
		return -1;
	}

	if ((XDF_DIFF_ALG(xpp->flags) != XDF_PATIENCE_DIFF) &&
	    (XDF_DIFF_ALG(xpp->flags) != XDF_HISTOGRAM_DIFF) &&
	    xdl_optimize_ctxs(&cf, &xe->xdf1, &xe->xdf2) < 0) {

		xdl_free_ctx(&xe->xdf2);
		xdl_free_ctx(&xe->xdf1);
		xdl_free_classifier(&cf);
		return -1;
	}

	if (XDF_DIFF_ALG(xpp->flags) != XDF_HISTOGRAM_DIFF)
		xdl_free_classifier(&cf);

	return 0;
}