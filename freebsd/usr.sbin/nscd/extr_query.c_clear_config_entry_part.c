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
struct configuration_entry {int /*<<< orphan*/ * negative_cache_entry; int /*<<< orphan*/ * positive_cache_entry; } ;
typedef  int /*<<< orphan*/  cache_entry ;

/* Variables and functions */
 int /*<<< orphan*/  CELT_MULTIPART ; 
 int /*<<< orphan*/  CELT_NEGATIVE ; 
 int /*<<< orphan*/  CELT_POSITIVE ; 
 int /*<<< orphan*/  CTT_CLEAR ; 
 int /*<<< orphan*/  KPPT_LEFT ; 
 int /*<<< orphan*/  TRACE_IN (void (*) (struct configuration_entry*,char const*,size_t)) ; 
 int /*<<< orphan*/  TRACE_OUT (void (*) (struct configuration_entry*,char const*,size_t)) ; 
 scalar_t__ configuration_entry_find_mp_cache_entries (struct configuration_entry*,char const*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  configuration_lock_entry (struct configuration_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  configuration_unlock_entry (struct configuration_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transform_cache_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transform_cache_entry_part (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
clear_config_entry_part(struct configuration_entry *config_entry,
	const char *eid_str, size_t eid_str_length)
{
	cache_entry *start, *finish, *mp_entry;
	TRACE_IN(clear_config_entry_part);
	configuration_lock_entry(config_entry, CELT_POSITIVE);
	if (config_entry->positive_cache_entry != NULL)
		transform_cache_entry_part(
			config_entry->positive_cache_entry,
			CTT_CLEAR, eid_str, eid_str_length, KPPT_LEFT);
	configuration_unlock_entry(config_entry, CELT_POSITIVE);

	configuration_lock_entry(config_entry, CELT_NEGATIVE);
	if (config_entry->negative_cache_entry != NULL)
		transform_cache_entry_part(
			config_entry->negative_cache_entry,
			CTT_CLEAR, eid_str, eid_str_length, KPPT_LEFT);
	configuration_unlock_entry(config_entry, CELT_NEGATIVE);

	configuration_lock_entry(config_entry, CELT_MULTIPART);
	if (configuration_entry_find_mp_cache_entries(config_entry,
		eid_str, &start, &finish) == 0) {
		for (mp_entry = start; mp_entry != finish; ++mp_entry)
			transform_cache_entry(*mp_entry, CTT_CLEAR);
	}
	configuration_unlock_entry(config_entry, CELT_MULTIPART);

	TRACE_OUT(clear_config_entry_part);
}