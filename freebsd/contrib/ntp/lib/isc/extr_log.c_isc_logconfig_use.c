#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ isc_result_t ;
struct TYPE_9__ {TYPE_2__* lctx; } ;
typedef  TYPE_1__ isc_logconfig_t ;
struct TYPE_10__ {int /*<<< orphan*/  lock; TYPE_1__* logconfig; } ;
typedef  TYPE_2__ isc_log_t ;

/* Variables and functions */
 scalar_t__ ISC_R_SUCCESS ; 
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int VALID_CONFIG (TYPE_1__*) ; 
 int VALID_CONTEXT (TYPE_2__*) ; 
 int /*<<< orphan*/  isc_logconfig_destroy (TYPE_1__**) ; 
 scalar_t__ sync_channellist (TYPE_1__*) ; 

isc_result_t
isc_logconfig_use(isc_log_t *lctx, isc_logconfig_t *lcfg) {
	isc_logconfig_t *old_cfg;
	isc_result_t result;

	REQUIRE(VALID_CONTEXT(lctx));
	REQUIRE(VALID_CONFIG(lcfg));
	REQUIRE(lcfg->lctx == lctx);

	/*
	 * Ensure that lcfg->channellist_count == lctx->category_count.
	 * They won't be equal if isc_log_usechannel has not been called
	 * since any call to isc_log_registercategories.
	 */
	result = sync_channellist(lcfg);
	if (result != ISC_R_SUCCESS)
		return (result);

	LOCK(&lctx->lock);

	old_cfg = lctx->logconfig;
	lctx->logconfig = lcfg;

	UNLOCK(&lctx->lock);

	isc_logconfig_destroy(&old_cfg);

	return (ISC_R_SUCCESS);
}