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
struct dentry {int dummy; } ;
struct debugfs_entries {int /*<<< orphan*/  reg; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_create_file_unsafe (int /*<<< orphan*/ ,int,struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fops_x32 ; 

__attribute__((used)) static void dw_edma_debugfs_create_x32(const struct debugfs_entries entries[],
				       int nr_entries, struct dentry *dir)
{
	int i;

	for (i = 0; i < nr_entries; i++) {
		if (!debugfs_create_file_unsafe(entries[i].name, 0444, dir,
						entries[i].reg,	&fops_x32))
			break;
	}
}