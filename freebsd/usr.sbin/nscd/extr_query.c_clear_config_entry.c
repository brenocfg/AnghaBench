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
struct configuration_entry {size_t mp_cache_entries_size; int /*<<< orphan*/ ** mp_cache_entries; int /*<<< orphan*/ * negative_cache_entry; int /*<<< orphan*/ * positive_cache_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  CELT_MULTIPART ; 
 int /*<<< orphan*/  CELT_NEGATIVE ; 
 int /*<<< orphan*/  CELT_POSITIVE ; 
 int /*<<< orphan*/  CTT_CLEAR ; 
 int /*<<< orphan*/  TRACE_IN (void (*) (struct configuration_entry*)) ; 
 int /*<<< orphan*/  TRACE_OUT (void (*) (struct configuration_entry*)) ; 
 int /*<<< orphan*/  configuration_lock_entry (struct configuration_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  configuration_unlock_entry (struct configuration_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transform_cache_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
clear_config_entry(struct configuration_entry *config_entry)
{
	size_t i;

	TRACE_IN(clear_config_entry);
	configuration_lock_entry(config_entry, CELT_POSITIVE);
	if (config_entry->positive_cache_entry != NULL)
		transform_cache_entry(
			config_entry->positive_cache_entry,
			CTT_CLEAR);
	configuration_unlock_entry(config_entry, CELT_POSITIVE);

	configuration_lock_entry(config_entry, CELT_NEGATIVE);
	if (config_entry->negative_cache_entry != NULL)
		transform_cache_entry(
			config_entry->negative_cache_entry,
			CTT_CLEAR);
	configuration_unlock_entry(config_entry, CELT_NEGATIVE);

	configuration_lock_entry(config_entry, CELT_MULTIPART);
	for (i = 0; i < config_entry->mp_cache_entries_size; ++i)
		transform_cache_entry(
			config_entry->mp_cache_entries[i],
			CTT_CLEAR);
	configuration_unlock_entry(config_entry, CELT_MULTIPART);

	TRACE_OUT(clear_config_entry);
}