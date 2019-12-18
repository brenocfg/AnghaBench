#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ id; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ isc_logmodule_t ;
struct TYPE_8__ {int /*<<< orphan*/  module_count; TYPE_1__* modules; } ;
typedef  TYPE_2__ isc_log_t ;

/* Variables and functions */
 int /*<<< orphan*/  DE_CONST (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 scalar_t__ UINT_MAX ; 
 int VALID_CONTEXT (TYPE_2__*) ; 

void
isc_log_registermodules(isc_log_t *lctx, isc_logmodule_t modules[]) {
	isc_logmodule_t *modp;

	REQUIRE(VALID_CONTEXT(lctx));
	REQUIRE(modules != NULL && modules[0].name != NULL);

	/*
	 * XXXDCL This somewhat sleazy situation of using the last pointer
	 * in one category array to point to the next array exists because
	 * this registration function returns void and I didn't want to have
	 * change everything that used it by making it return an isc_result_t.
	 * It would need to do that if it had to allocate memory to store
	 * pointers to each array passed in.
	 */
	if (lctx->modules == NULL)
		lctx->modules = modules;

	else {
		/*
		 * Adjust the last (NULL) pointer of the already registered
		 * modules to point to the incoming array.
		 */
		for (modp = lctx->modules; modp->name != NULL; )
			if (modp->id == UINT_MAX)
				/*
				 * The name pointer points to the next array.
				 * Ick.
				 */
				DE_CONST(modp->name, modp);
			else
				modp++;

		modp->name = (void *)modules;
		modp->id = UINT_MAX;
	}

	/*
	 * Update the id number of the module with its new global id.
	 */
	for (modp = modules; modp->name != NULL; modp++)
		modp->id = lctx->module_count++;
}