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
typedef  int /*<<< orphan*/  isc_timermgr_t ;
typedef  scalar_t__ isc_result_t ;
typedef  int /*<<< orphan*/  isc_mem_t ;
typedef  int /*<<< orphan*/  isc_appctx_t ;

/* Variables and functions */
 scalar_t__ ISC_R_SUCCESS ; 
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  createlock ; 
 int /*<<< orphan*/  isc_appctx_settimermgr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ timermgr_createfunc (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

isc_result_t
isc_timermgr_createinctx(isc_mem_t *mctx, isc_appctx_t *actx,
			 isc_timermgr_t **managerp)
{
	isc_result_t result;

	LOCK(&createlock);

	REQUIRE(timermgr_createfunc != NULL);
	result = (*timermgr_createfunc)(mctx, managerp);

	UNLOCK(&createlock);

	if (result == ISC_R_SUCCESS)
		isc_appctx_settimermgr(actx, *managerp);

	return (result);
}