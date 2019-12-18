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
typedef  int /*<<< orphan*/  zprop_source_t ;
typedef  char const uint64_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  intval ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 scalar_t__ DATA_TYPE_BOOLEAN ; 
 scalar_t__ DATA_TYPE_NVLIST ; 
 scalar_t__ DATA_TYPE_STRING ; 
 scalar_t__ DATA_TYPE_UINT64 ; 
 int /*<<< orphan*/  ZPROP_VALUE ; 
 int /*<<< orphan*/  dsl_prop_set_sync_impl (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int,int,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fnvlist_lookup_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fnvpair_value_nvlist (int /*<<< orphan*/ *) ; 
 char* fnvpair_value_string (int /*<<< orphan*/ *) ; 
 char fnvpair_value_uint64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 scalar_t__ nvpair_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int strlen (char const*) ; 

void
dsl_props_set_sync_impl(dsl_dataset_t *ds, zprop_source_t source,
    nvlist_t *props, dmu_tx_t *tx)
{
	nvpair_t *elem = NULL;

	while ((elem = nvlist_next_nvpair(props, elem)) != NULL) {
		nvpair_t *pair = elem;
		const char *name = nvpair_name(pair);

		if (nvpair_type(pair) == DATA_TYPE_NVLIST) {
			/*
			 * This usually happens when we reuse the nvlist_t data
			 * returned by the counterpart dsl_prop_get_all_impl().
			 * For instance we do this to restore the original
			 * received properties when an error occurs in the
			 * zfs_ioc_recv() codepath.
			 */
			nvlist_t *attrs = fnvpair_value_nvlist(pair);
			pair = fnvlist_lookup_nvpair(attrs, ZPROP_VALUE);
		}

		if (nvpair_type(pair) == DATA_TYPE_STRING) {
			const char *value = fnvpair_value_string(pair);
			dsl_prop_set_sync_impl(ds, name,
			    source, 1, strlen(value) + 1, value, tx);
		} else if (nvpair_type(pair) == DATA_TYPE_UINT64) {
			uint64_t intval = fnvpair_value_uint64(pair);
			dsl_prop_set_sync_impl(ds, name,
			    source, sizeof (intval), 1, &intval, tx);
		} else if (nvpair_type(pair) == DATA_TYPE_BOOLEAN) {
			dsl_prop_set_sync_impl(ds, name,
			    source, 0, 0, NULL, tx);
		} else {
			panic("invalid nvpair type");
		}
	}
}