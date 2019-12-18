#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ isc_result_t ;
struct TYPE_13__ {scalar_t__ id; } ;
typedef  TYPE_1__ isc_logmodule_t ;
struct TYPE_14__ {scalar_t__ highest_level; int /*<<< orphan*/  dynamic; int /*<<< orphan*/ * channellists; TYPE_5__* lctx; } ;
typedef  TYPE_2__ isc_logconfig_t ;
struct TYPE_15__ {TYPE_1__ const* module; TYPE_4__* channel; } ;
typedef  TYPE_3__ isc_logchannellist_t ;
struct TYPE_16__ {scalar_t__ type; scalar_t__ level; } ;
typedef  TYPE_4__ isc_logchannel_t ;
struct TYPE_17__ {unsigned int category_count; scalar_t__ module_count; int /*<<< orphan*/  mctx; } ;
typedef  TYPE_5__ isc_log_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_LIST_INITANDPREPEND (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ISC_LOG_DYNAMIC ; 
 scalar_t__ ISC_LOG_TONULL ; 
 scalar_t__ ISC_R_NOMEMORY ; 
 scalar_t__ ISC_R_SUCCESS ; 
 int /*<<< orphan*/  ISC_TRUE ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int VALID_CONFIG (TYPE_2__*) ; 
 TYPE_3__* isc_mem_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  link ; 
 scalar_t__ sync_channellist (TYPE_2__*) ; 

__attribute__((used)) static isc_result_t
assignchannel(isc_logconfig_t *lcfg, unsigned int category_id,
	      const isc_logmodule_t *module, isc_logchannel_t *channel)
{
	isc_logchannellist_t *new_item;
	isc_log_t *lctx;
	isc_result_t result;

	REQUIRE(VALID_CONFIG(lcfg));

	lctx = lcfg->lctx;

	REQUIRE(category_id < lctx->category_count);
	REQUIRE(module == NULL || module->id < lctx->module_count);
	REQUIRE(channel != NULL);

	/*
	 * Ensure lcfg->channellist_count == lctx->category_count.
	 */
	result = sync_channellist(lcfg);
	if (result != ISC_R_SUCCESS)
		return (result);

	new_item = isc_mem_get(lctx->mctx, sizeof(*new_item));
	if (new_item == NULL)
		return (ISC_R_NOMEMORY);

	new_item->channel = channel;
	new_item->module = module;
	ISC_LIST_INITANDPREPEND(lcfg->channellists[category_id],
			       new_item, link);

	/*
	 * Remember the highest logging level set by any channel in the
	 * logging config, so isc_log_doit() can quickly return if the
	 * message is too high to be logged by any channel.
	 */
	if (channel->type != ISC_LOG_TONULL) {
		if (lcfg->highest_level < channel->level)
			lcfg->highest_level = channel->level;
		if (channel->level == ISC_LOG_DYNAMIC)
			lcfg->dynamic = ISC_TRUE;
	}

	return (ISC_R_SUCCESS);
}