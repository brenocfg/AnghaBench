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
typedef  TYPE_1__ isc_logcategory_t ;
struct TYPE_8__ {TYPE_1__* categories; } ;
typedef  TYPE_2__ isc_log_t ;

/* Variables and functions */
 int /*<<< orphan*/  DE_CONST (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 scalar_t__ UINT_MAX ; 
 int /*<<< orphan*/  VALID_CONTEXT (TYPE_2__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 

isc_logcategory_t *
isc_log_categorybyname(isc_log_t *lctx, const char *name) {
	isc_logcategory_t *catp;

	REQUIRE(VALID_CONTEXT(lctx));
	REQUIRE(name != NULL);

	for (catp = lctx->categories; catp->name != NULL; )
		if (catp->id == UINT_MAX)
			/*
			 * catp is neither modified nor returned to the
			 * caller, so removing its const qualifier is ok.
			 */
			DE_CONST(catp->name, catp);
		else {
			if (strcmp(catp->name, name) == 0)
				return (catp);
			catp++;
		}

	return (NULL);
}