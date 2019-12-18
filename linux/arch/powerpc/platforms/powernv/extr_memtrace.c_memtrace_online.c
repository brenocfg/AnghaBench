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
struct memtrace_entry {scalar_t__ nid; scalar_t__ start; scalar_t__ size; int /*<<< orphan*/  dir; scalar_t__ mem; } ;

/* Variables and functions */
 scalar_t__ NUMA_NO_NODE ; 
 scalar_t__ add_memory (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct memtrace_entry*) ; 
 int /*<<< orphan*/  lock_device_hotplug () ; 
 int /*<<< orphan*/  memhp_auto_online ; 
 struct memtrace_entry* memtrace_array ; 
 int memtrace_array_nr ; 
 scalar_t__ memtrace_size ; 
 int /*<<< orphan*/  online_mem_block ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 
 int /*<<< orphan*/  pr_info (char*,scalar_t__) ; 
 int /*<<< orphan*/  unlock_device_hotplug () ; 
 int /*<<< orphan*/  walk_memory_blocks (scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int memtrace_online(void)
{
	int i, ret = 0;
	struct memtrace_entry *ent;

	for (i = memtrace_array_nr - 1; i >= 0; i--) {
		ent = &memtrace_array[i];

		/* We have onlined this chunk previously */
		if (ent->nid == NUMA_NO_NODE)
			continue;

		/* Remove from io mappings */
		if (ent->mem) {
			iounmap(ent->mem);
			ent->mem = 0;
		}

		if (add_memory(ent->nid, ent->start, ent->size)) {
			pr_err("Failed to add trace memory to node %d\n",
				ent->nid);
			ret += 1;
			continue;
		}

		/*
		 * If kernel isn't compiled with the auto online option
		 * we need to online the memory ourselves.
		 */
		if (!memhp_auto_online) {
			lock_device_hotplug();
			walk_memory_blocks(ent->start, ent->size, NULL,
					   online_mem_block);
			unlock_device_hotplug();
		}

		/*
		 * Memory was added successfully so clean up references to it
		 * so on reentry we can tell that this chunk was added.
		 */
		debugfs_remove_recursive(ent->dir);
		pr_info("Added trace memory back to node %d\n", ent->nid);
		ent->size = ent->start = ent->nid = NUMA_NO_NODE;
	}
	if (ret)
		return ret;

	/* If all chunks of memory were added successfully, reset globals */
	kfree(memtrace_array);
	memtrace_array = NULL;
	memtrace_size = 0;
	memtrace_array_nr = 0;
	return 0;
}