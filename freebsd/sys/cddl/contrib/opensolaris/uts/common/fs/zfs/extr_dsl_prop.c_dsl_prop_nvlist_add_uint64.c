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
typedef  int /*<<< orphan*/  zfs_prop_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  ZPROP_SOURCE ; 
 int /*<<< orphan*/  ZPROP_VALUE ; 
 scalar_t__ dodefault (int /*<<< orphan*/ ,int,int,scalar_t__*) ; 
 scalar_t__ nvlist_add_nvlist (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ nvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ **) ; 
 char* zfs_prop_to_name (int /*<<< orphan*/ ) ; 

void
dsl_prop_nvlist_add_uint64(nvlist_t *nv, zfs_prop_t prop, uint64_t value)
{
	nvlist_t *propval;
	const char *propname = zfs_prop_to_name(prop);
	uint64_t default_value;

	if (nvlist_lookup_nvlist(nv, propname, &propval) == 0) {
		VERIFY(nvlist_add_uint64(propval, ZPROP_VALUE, value) == 0);
		return;
	}

	VERIFY(nvlist_alloc(&propval, NV_UNIQUE_NAME, KM_SLEEP) == 0);
	VERIFY(nvlist_add_uint64(propval, ZPROP_VALUE, value) == 0);
	/* Indicate the default source if we can. */
	if (dodefault(prop, 8, 1, &default_value) == 0 &&
	    value == default_value) {
		VERIFY(nvlist_add_string(propval, ZPROP_SOURCE, "") == 0);
	}
	VERIFY(nvlist_add_nvlist(nv, propname, propval) == 0);
	nvlist_free(propval);
}