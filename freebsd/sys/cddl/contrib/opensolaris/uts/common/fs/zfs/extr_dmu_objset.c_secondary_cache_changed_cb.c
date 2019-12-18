#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_2__ {scalar_t__ os_secondary_cache; } ;
typedef  TYPE_1__ objset_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ ZFS_CACHE_ALL ; 
 scalar_t__ ZFS_CACHE_METADATA ; 
 scalar_t__ ZFS_CACHE_NONE ; 

__attribute__((used)) static void
secondary_cache_changed_cb(void *arg, uint64_t newval)
{
	objset_t *os = arg;

	/*
	 * Inheritance and range checking should have been done by now.
	 */
	ASSERT(newval == ZFS_CACHE_ALL || newval == ZFS_CACHE_NONE ||
	    newval == ZFS_CACHE_METADATA);

	os->os_secondary_cache = newval;
}