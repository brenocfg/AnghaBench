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
struct TYPE_4__ {unsigned int duplicate_interval; } ;
typedef  TYPE_1__ isc_logconfig_t ;

/* Variables and functions */
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALID_CONTEXT (TYPE_1__*) ; 

unsigned int
isc_log_getduplicateinterval(isc_logconfig_t *lcfg) {
	REQUIRE(VALID_CONTEXT(lcfg));

	return (lcfg->duplicate_interval);
}