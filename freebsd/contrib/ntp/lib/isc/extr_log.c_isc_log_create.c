#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ isc_result_t ;
typedef  int /*<<< orphan*/  isc_mem_t ;
typedef  int /*<<< orphan*/  isc_logconfig_t ;
struct TYPE_9__ {int /*<<< orphan*/ * logconfig; int /*<<< orphan*/  magic; int /*<<< orphan*/  lock; int /*<<< orphan*/  messages; scalar_t__ debug_level; scalar_t__ module_count; int /*<<< orphan*/ * modules; scalar_t__ category_count; int /*<<< orphan*/ * categories; int /*<<< orphan*/ * mctx; } ;
typedef  TYPE_1__ isc_log_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_LIST_INIT (int /*<<< orphan*/ ) ; 
 scalar_t__ ISC_R_NOMEMORY ; 
 scalar_t__ ISC_R_SUCCESS ; 
 int /*<<< orphan*/  LCTX_MAGIC ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  isc_categories ; 
 int /*<<< orphan*/  isc_log_destroy (TYPE_1__**) ; 
 int /*<<< orphan*/  isc_log_registercategories (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isc_log_registermodules (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ isc_logconfig_create (TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  isc_logconfig_destroy (int /*<<< orphan*/ **) ; 
 TYPE_1__* isc_mem_get (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  isc_mem_put (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  isc_modules ; 
 scalar_t__ isc_mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ sync_channellist (int /*<<< orphan*/ *) ; 

isc_result_t
isc_log_create(isc_mem_t *mctx, isc_log_t **lctxp, isc_logconfig_t **lcfgp) {
	isc_log_t *lctx;
	isc_logconfig_t *lcfg = NULL;
	isc_result_t result;

	REQUIRE(mctx != NULL);
	REQUIRE(lctxp != NULL && *lctxp == NULL);
	REQUIRE(lcfgp == NULL || *lcfgp == NULL);

	lctx = isc_mem_get(mctx, sizeof(*lctx));
	if (lctx != NULL) {
		lctx->mctx = mctx;
		lctx->categories = NULL;
		lctx->category_count = 0;
		lctx->modules = NULL;
		lctx->module_count = 0;
		lctx->debug_level = 0;

		ISC_LIST_INIT(lctx->messages);

		result = isc_mutex_init(&lctx->lock);
		if (result != ISC_R_SUCCESS) {
			isc_mem_put(mctx, lctx, sizeof(*lctx));
			return (result);
		}

		/*
		 * Normally setting the magic number is the last step done
		 * in a creation function, but a valid log context is needed
		 * by isc_log_registercategories and isc_logconfig_create.
		 * If either fails, the lctx is destroyed and not returned
		 * to the caller.
		 */
		lctx->magic = LCTX_MAGIC;

		isc_log_registercategories(lctx, isc_categories);
		isc_log_registermodules(lctx, isc_modules);
		result = isc_logconfig_create(lctx, &lcfg);

	} else
		result = ISC_R_NOMEMORY;

	if (result == ISC_R_SUCCESS)
		result = sync_channellist(lcfg);

	if (result == ISC_R_SUCCESS) {
		lctx->logconfig = lcfg;

		*lctxp = lctx;
		if (lcfgp != NULL)
			*lcfgp = lcfg;

	} else {
		if (lcfg != NULL)
			isc_logconfig_destroy(&lcfg);
		if (lctx != NULL)
			isc_log_destroy(&lctx);
	}

	return (result);
}