#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_logconfig_t ;
struct TYPE_4__ {int /*<<< orphan*/ * logconfig; } ;
typedef  TYPE_1__ isc_log_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENSURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALID_CONTEXT (TYPE_1__*) ; 

isc_logconfig_t *
isc_logconfig_get(isc_log_t *lctx) {
	REQUIRE(VALID_CONTEXT(lctx));

	ENSURE(lctx->logconfig != NULL);

	return (lctx->logconfig);
}