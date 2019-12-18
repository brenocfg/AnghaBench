#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ isc_result_t ;
struct TYPE_16__ {scalar_t__ id; } ;
typedef  TYPE_1__ isc_logmodule_t ;
struct TYPE_17__ {int /*<<< orphan*/  channels; TYPE_5__* lctx; } ;
typedef  TYPE_2__ isc_logconfig_t ;
struct TYPE_18__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ isc_logchannel_t ;
struct TYPE_19__ {unsigned int id; } ;
typedef  TYPE_4__ isc_logcategory_t ;
struct TYPE_20__ {unsigned int category_count; scalar_t__ module_count; } ;
typedef  TYPE_5__ isc_log_t ;

/* Variables and functions */
 TYPE_3__* ISC_LIST_HEAD (int /*<<< orphan*/ ) ; 
 TYPE_3__* ISC_LIST_NEXT (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ISC_R_NOTFOUND ; 
 scalar_t__ ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int VALID_CONFIG (TYPE_2__*) ; 
 scalar_t__ assignchannel (TYPE_2__*,unsigned int,TYPE_1__ const*,TYPE_3__*) ; 
 int /*<<< orphan*/  link ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

isc_result_t
isc_log_usechannel(isc_logconfig_t *lcfg, const char *name,
		   const isc_logcategory_t *category,
		   const isc_logmodule_t *module)
{
	isc_log_t *lctx;
	isc_logchannel_t *channel;
	isc_result_t result = ISC_R_SUCCESS;
	unsigned int i;

	REQUIRE(VALID_CONFIG(lcfg));
	REQUIRE(name != NULL);

	lctx = lcfg->lctx;

	REQUIRE(category == NULL || category->id < lctx->category_count);
	REQUIRE(module == NULL || module->id < lctx->module_count);

	for (channel = ISC_LIST_HEAD(lcfg->channels); channel != NULL;
	     channel = ISC_LIST_NEXT(channel, link))
		if (strcmp(name, channel->name) == 0)
			break;

	if (channel == NULL)
		return (ISC_R_NOTFOUND);

	if (category != NULL)
		result = assignchannel(lcfg, category->id, module, channel);

	else
		/*
		 * Assign to all categories.  Note that this includes
		 * the default channel.
		 */
		for (i = 0; i < lctx->category_count; i++) {
			result = assignchannel(lcfg, i, module, channel);
			if (result != ISC_R_SUCCESS)
				break;
		}

	return (result);
}