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
struct configuration_entry {int mp_cache_entries_size; int /*<<< orphan*/ * mp_cache_entries; } ;
typedef  int /*<<< orphan*/  cache_entry ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_IN (int (*) (struct configuration_entry*,int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  TRACE_OUT (int (*) (struct configuration_entry*,int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  configuration_entry_cache_mp_sort_cmp ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 

int
configuration_entry_add_mp_cache_entry(struct configuration_entry *config_entry,
	cache_entry c_entry)
{
	cache_entry *new_mp_entries, *old_mp_entries;

	TRACE_IN(configuration_entry_add_mp_cache_entry);
	++config_entry->mp_cache_entries_size;
	new_mp_entries = malloc(sizeof(*new_mp_entries) *
		config_entry->mp_cache_entries_size);
	assert(new_mp_entries != NULL);
	new_mp_entries[0] = c_entry;

	if (config_entry->mp_cache_entries_size - 1 > 0) {
		memcpy(new_mp_entries + 1,
		    config_entry->mp_cache_entries,
		    (config_entry->mp_cache_entries_size - 1) *
		    sizeof(cache_entry));
	}

	old_mp_entries = config_entry->mp_cache_entries;
	config_entry->mp_cache_entries = new_mp_entries;
	free(old_mp_entries);

	qsort(config_entry->mp_cache_entries,
		config_entry->mp_cache_entries_size,
		sizeof(cache_entry),
		configuration_entry_cache_mp_sort_cmp);

	TRACE_OUT(configuration_entry_add_mp_cache_entry);
	return (0);
}