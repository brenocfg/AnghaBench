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
struct configuration_entry {int /*<<< orphan*/  mp_cache_entries_size; int /*<<< orphan*/  mp_cache_entries; } ;
typedef  int /*<<< orphan*/ * cache_entry ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_IN (int /*<<< orphan*/ * (*) (struct configuration_entry*,char const*)) ; 
 int /*<<< orphan*/  TRACE_OUT (int /*<<< orphan*/ * (*) (struct configuration_entry*,char const*)) ; 
 int /*<<< orphan*/ ** bsearch (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  configuration_entry_cache_mp_cmp ; 

cache_entry
configuration_entry_find_mp_cache_entry(
	struct configuration_entry *config_entry, const char *mp_name)
{
	cache_entry *result;

	TRACE_IN(configuration_entry_find_mp_cache_entry);
	result = bsearch(mp_name, config_entry->mp_cache_entries,
		config_entry->mp_cache_entries_size,
		sizeof(cache_entry), configuration_entry_cache_mp_cmp);

	if (result == NULL) {
		TRACE_OUT(configuration_entry_find_mp_cache_entry);
		return (NULL);
	} else {
		TRACE_OUT(configuration_entry_find_mp_cache_entry);
		return (*result);
	}
}