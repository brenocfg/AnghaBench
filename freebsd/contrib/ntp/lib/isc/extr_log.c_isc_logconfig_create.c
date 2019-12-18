#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
typedef  scalar_t__ isc_result_t ;
struct TYPE_14__ {scalar_t__ maximum_size; void* versions; int /*<<< orphan*/ * name; void* stream; } ;
struct TYPE_15__ {TYPE_1__ file; int /*<<< orphan*/  facility; } ;
typedef  TYPE_2__ isc_logdestination_t ;
struct TYPE_16__ {int highest_level; int /*<<< orphan*/  channels; int /*<<< orphan*/  magic; int /*<<< orphan*/  dynamic; int /*<<< orphan*/ * tag; scalar_t__ duplicate_interval; scalar_t__ channellist_count; int /*<<< orphan*/ * channellists; TYPE_4__* lctx; } ;
typedef  TYPE_3__ isc_logconfig_t ;
struct TYPE_17__ {int /*<<< orphan*/  mctx; } ;
typedef  TYPE_4__ isc_log_t ;
struct TYPE_13__ {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_FALSE ; 
 int /*<<< orphan*/  ISC_LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_LIST_INIT (int /*<<< orphan*/ ) ; 
 int ISC_LOG_DYNAMIC ; 
 int ISC_LOG_INFO ; 
 int /*<<< orphan*/  ISC_LOG_PRINTTIME ; 
 void* ISC_LOG_ROLLNEVER ; 
 int /*<<< orphan*/  ISC_LOG_TOFILEDESC ; 
 int /*<<< orphan*/  ISC_LOG_TONULL ; 
 int /*<<< orphan*/  ISC_LOG_TOSYSLOG ; 
 scalar_t__ ISC_R_NOMEMORY ; 
 scalar_t__ ISC_R_SUCCESS ; 
 int /*<<< orphan*/  LCFG_MAGIC ; 
 int /*<<< orphan*/  LOG_DAEMON ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int VALID_CONTEXT (TYPE_4__*) ; 
 TYPE_11__ default_channel ; 
 scalar_t__ isc_log_createchannel (TYPE_3__*,char*,int /*<<< orphan*/ ,int,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isc_logconfig_destroy (TYPE_3__**) ; 
 TYPE_3__* isc_mem_get (int /*<<< orphan*/ ,int) ; 
 void* stderr ; 

isc_result_t
isc_logconfig_create(isc_log_t *lctx, isc_logconfig_t **lcfgp) {
	isc_logconfig_t *lcfg;
	isc_logdestination_t destination;
	isc_result_t result = ISC_R_SUCCESS;
	int level = ISC_LOG_INFO;

	REQUIRE(lcfgp != NULL && *lcfgp == NULL);
	REQUIRE(VALID_CONTEXT(lctx));

	lcfg = isc_mem_get(lctx->mctx, sizeof(*lcfg));

	if (lcfg != NULL) {
		lcfg->lctx = lctx;
		lcfg->channellists = NULL;
		lcfg->channellist_count = 0;
		lcfg->duplicate_interval = 0;
		lcfg->highest_level = level;
		lcfg->tag = NULL;
		lcfg->dynamic = ISC_FALSE;

		ISC_LIST_INIT(lcfg->channels);

		/*
		 * Normally the magic number is the last thing set in the
		 * structure, but isc_log_createchannel() needs a valid
		 * config.  If the channel creation fails, the lcfg is not
		 * returned to the caller.
		 */
		lcfg->magic = LCFG_MAGIC;

	} else
		result = ISC_R_NOMEMORY;

	/*
	 * Create the default channels:
	 *   	default_syslog, default_stderr, default_debug and null.
	 */
	if (result == ISC_R_SUCCESS) {
		destination.facility = LOG_DAEMON;
		result = isc_log_createchannel(lcfg, "default_syslog",
					       ISC_LOG_TOSYSLOG, level,
					       &destination, 0);
	}

	if (result == ISC_R_SUCCESS) {
		destination.file.stream = stderr;
		destination.file.name = NULL;
		destination.file.versions = ISC_LOG_ROLLNEVER;
		destination.file.maximum_size = 0;
		result = isc_log_createchannel(lcfg, "default_stderr",
					       ISC_LOG_TOFILEDESC,
					       level,
					       &destination,
					       ISC_LOG_PRINTTIME);
	}

	if (result == ISC_R_SUCCESS) {
		/*
		 * Set the default category's channel to default_stderr,
		 * which is at the head of the channels list because it was
		 * just created.
		 */
		default_channel.channel = ISC_LIST_HEAD(lcfg->channels);

		destination.file.stream = stderr;
		destination.file.name = NULL;
		destination.file.versions = ISC_LOG_ROLLNEVER;
		destination.file.maximum_size = 0;
		result = isc_log_createchannel(lcfg, "default_debug",
					       ISC_LOG_TOFILEDESC,
					       ISC_LOG_DYNAMIC,
					       &destination,
					       ISC_LOG_PRINTTIME);
	}

	if (result == ISC_R_SUCCESS)
		result = isc_log_createchannel(lcfg, "null",
					       ISC_LOG_TONULL,
					       ISC_LOG_DYNAMIC,
					       NULL, 0);

	if (result == ISC_R_SUCCESS)
		*lcfgp = lcfg;

	else
		if (lcfg != NULL)
			isc_logconfig_destroy(&lcfg);

	return (result);
}