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
struct partition_entry {int size; int /*<<< orphan*/  flags; } ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int daddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  HRDBG (char*,char const*) ; 
 int /*<<< orphan*/  HR_PARTITION_FOUND ; 
 int INT_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 struct partition_entry* partition_entry_create (int /*<<< orphan*/ ,char const*) ; 
 struct partition_entry* partition_entry_find_by_name (char const*) ; 

__attribute__((used)) static void
handle_chunk(int32_t ds_index, const char *chunk_name, off_t chunk_size)
{
	struct partition_entry *entry;
	daddr_t k_size;

	assert(chunk_name != NULL);
	assert(chunk_name[0] != '\0');
	if (chunk_name == NULL || chunk_name[0] == '\0')
		return;

	HRDBG("ANALYZE chunk %s", chunk_name);

	if ((entry = partition_entry_find_by_name(chunk_name)) == NULL)
		if ((entry = partition_entry_create(ds_index,
		    chunk_name)) == NULL)
			return;

	entry->flags |= HR_PARTITION_FOUND;

	/* actual size may overflow the SNMP type */
	k_size = chunk_size / 1024;
	entry->size = (k_size > (off_t)INT_MAX ? INT_MAX : k_size);
}