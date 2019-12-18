#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vm_address_t ;
typedef  int /*<<< orphan*/  malloc_zone_t ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/ * malloc_default_zone () ; 
 scalar_t__ malloc_get_all_zones (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,unsigned int*) ; 

__attribute__((used)) static malloc_zone_t *
zone_default_get(void) {
	malloc_zone_t **zones = NULL;
	unsigned int num_zones = 0;

	/*
	 * On OSX 10.12, malloc_default_zone returns a special zone that is not
	 * present in the list of registered zones. That zone uses a "lite zone"
	 * if one is present (apparently enabled when malloc stack logging is
	 * enabled), or the first registered zone otherwise. In practice this
	 * means unless malloc stack logging is enabled, the first registered
	 * zone is the default.  So get the list of zones to get the first one,
	 * instead of relying on malloc_default_zone.
	 */
	if (KERN_SUCCESS != malloc_get_all_zones(0, NULL,
	    (vm_address_t**)&zones, &num_zones)) {
		/*
		 * Reset the value in case the failure happened after it was
		 * set.
		 */
		num_zones = 0;
	}

	if (num_zones) {
		return zones[0];
	}

	return malloc_default_zone();
}