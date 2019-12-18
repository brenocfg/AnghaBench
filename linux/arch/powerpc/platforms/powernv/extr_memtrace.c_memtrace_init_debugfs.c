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
struct memtrace_entry {int start; int size; int nid; struct dentry* dir; int /*<<< orphan*/  name; int /*<<< orphan*/  mem; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 struct dentry* debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,struct dentry*,struct memtrace_entry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_x64 (char*,int,struct dentry*,int*) ; 
 int /*<<< orphan*/  ioremap (int,int) ; 
 struct memtrace_entry* memtrace_array ; 
 int memtrace_array_nr ; 
 int /*<<< orphan*/  memtrace_debugfs_dir ; 
 int /*<<< orphan*/  memtrace_fops ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 

__attribute__((used)) static int memtrace_init_debugfs(void)
{
	int ret = 0;
	int i;

	for (i = 0; i < memtrace_array_nr; i++) {
		struct dentry *dir;
		struct memtrace_entry *ent = &memtrace_array[i];

		ent->mem = ioremap(ent->start, ent->size);
		/* Warn but continue on */
		if (!ent->mem) {
			pr_err("Failed to map trace memory at 0x%llx\n",
				 ent->start);
			ret = -1;
			continue;
		}

		snprintf(ent->name, 16, "%08x", ent->nid);
		dir = debugfs_create_dir(ent->name, memtrace_debugfs_dir);
		if (!dir) {
			pr_err("Failed to create debugfs directory for node %d\n",
				ent->nid);
			return -1;
		}

		ent->dir = dir;
		debugfs_create_file("trace", 0400, dir, ent, &memtrace_fops);
		debugfs_create_x64("start", 0400, dir, &ent->start);
		debugfs_create_x64("size", 0400, dir, &ent->size);
	}

	return ret;
}