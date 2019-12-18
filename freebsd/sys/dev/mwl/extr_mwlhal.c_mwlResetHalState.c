#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mwl_hal_priv {int mh_bastreams; int mh_flags; scalar_t__ mh_FCSErrorCount; scalar_t__ mh_RxDuplicateFrames; scalar_t__ mh_RTSFailures; scalar_t__ mh_RTSSuccesses; TYPE_1__* mh_vaps; } ;
struct TYPE_2__ {int /*<<< orphan*/ * mh; } ;

/* Variables and functions */
 int MHF_CALDATA ; 
 int MWL_BASTREAMS_MAX ; 
 int MWL_MBSS_MAX ; 
 int /*<<< orphan*/  mwlGetPwrCalTable (struct mwl_hal_priv*) ; 

__attribute__((used)) static int
mwlResetHalState(struct mwl_hal_priv *mh)
{
	int i;

	/* XXX get from f/w */
	mh->mh_bastreams = (1<<MWL_BASTREAMS_MAX)-1;
	for (i = 0; i < MWL_MBSS_MAX; i++)
		mh->mh_vaps[i].mh = NULL;
	/*
	 * Clear cumulative stats.
	 */
	mh->mh_RTSSuccesses = 0;
	mh->mh_RTSFailures = 0;
	mh->mh_RxDuplicateFrames = 0;
	mh->mh_FCSErrorCount = 0;
	/*
	 * Fetch cal data for later use.
	 * XXX may want to fetch other stuff too.
	 */
	/* XXX check return */
	if ((mh->mh_flags & MHF_CALDATA) == 0)
		mwlGetPwrCalTable(mh);
	return 0;
}