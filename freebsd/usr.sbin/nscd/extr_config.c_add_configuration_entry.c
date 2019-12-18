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
struct configuration_entry {int /*<<< orphan*/ * name; } ;
struct configuration {int entries_size; int entries_capacity; struct configuration_entry** entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_IN (int (*) (struct configuration*,struct configuration_entry*)) ; 
 int /*<<< orphan*/  TRACE_OUT (int (*) (struct configuration*,struct configuration_entry*)) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct configuration_entry** calloc (int,int) ; 
 int /*<<< orphan*/  configuration_entry_sort_cmp ; 
 int /*<<< orphan*/ * configuration_find_entry (struct configuration*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct configuration_entry**) ; 
 int /*<<< orphan*/  memcpy (struct configuration_entry**,struct configuration_entry**,int) ; 
 int /*<<< orphan*/  qsort (struct configuration_entry**,int,int,int /*<<< orphan*/ ) ; 

int
add_configuration_entry(struct configuration *config,
	struct configuration_entry *entry)
{
	TRACE_IN(add_configuration_entry);
	assert(entry != NULL);
	assert(entry->name != NULL);
	if (configuration_find_entry(config, entry->name) != NULL) {
		TRACE_OUT(add_configuration_entry);
		return (-1);
	}

	if (config->entries_size == config->entries_capacity) {
		struct configuration_entry **new_entries;

		config->entries_capacity *= 2;
		new_entries = calloc(config->entries_capacity,
			sizeof(*new_entries));
		assert(new_entries != NULL);
		memcpy(new_entries, config->entries,
			sizeof(struct configuration_entry *) *
		        config->entries_size);

		free(config->entries);
		config->entries = new_entries;
	}

	config->entries[config->entries_size++] = entry;
	qsort(config->entries, config->entries_size,
		sizeof(struct configuration_entry *),
		configuration_entry_sort_cmp);

	TRACE_OUT(add_configuration_entry);
	return (0);
}