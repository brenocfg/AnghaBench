#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_mem_t ;
struct TYPE_8__ {char* buffer; scalar_t__ magic; int /*<<< orphan*/ * mctx; scalar_t__ module_count; int /*<<< orphan*/ * modules; scalar_t__ category_count; int /*<<< orphan*/ * categories; scalar_t__ debug_level; int /*<<< orphan*/  text; int /*<<< orphan*/  messages; int /*<<< orphan*/  lock; int /*<<< orphan*/ * logconfig; } ;
typedef  TYPE_1__ isc_logmessage_t ;
typedef  int /*<<< orphan*/  isc_logconfig_t ;
typedef  TYPE_1__ isc_log_t ;

/* Variables and functions */
 int /*<<< orphan*/  DESTROYLOCK (int /*<<< orphan*/ *) ; 
 TYPE_1__* ISC_LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_LIST_UNLINK (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 scalar_t__ VALID_CONTEXT (TYPE_1__*) ; 
 int /*<<< orphan*/  isc_logconfig_destroy (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  isc_mem_put (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  link ; 
 int strlen (int /*<<< orphan*/ ) ; 

void
isc_log_destroy(isc_log_t **lctxp) {
	isc_log_t *lctx;
	isc_logconfig_t *lcfg;
	isc_mem_t *mctx;
	isc_logmessage_t *message;

	REQUIRE(lctxp != NULL && VALID_CONTEXT(*lctxp));

	lctx = *lctxp;
	mctx = lctx->mctx;

	if (lctx->logconfig != NULL) {
		lcfg = lctx->logconfig;
		lctx->logconfig = NULL;
		isc_logconfig_destroy(&lcfg);
	}

	DESTROYLOCK(&lctx->lock);

	while ((message = ISC_LIST_HEAD(lctx->messages)) != NULL) {
		ISC_LIST_UNLINK(lctx->messages, message, link);

		isc_mem_put(mctx, message,
			    sizeof(*message) + strlen(message->text) + 1);
	}

	lctx->buffer[0] = '\0';
	lctx->debug_level = 0;
	lctx->categories = NULL;
	lctx->category_count = 0;
	lctx->modules = NULL;
	lctx->module_count = 0;
	lctx->mctx = NULL;
	lctx->magic = 0;

	isc_mem_put(mctx, lctx, sizeof(*lctx));

	*lctxp = NULL;
}