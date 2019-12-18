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
struct debugfs_entry {int /*<<< orphan*/  fops; int /*<<< orphan*/  mode; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_EDAC_DEBUG ; 
 int ENOENT ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 struct dentry* edac_debugfs_create_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dentry*,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int thunderx_create_debugfs_nodes(struct dentry *parent,
					  struct debugfs_entry *attrs[],
					  void *data,
					  size_t num)
{
	int i;
	struct dentry *ent;

	if (!IS_ENABLED(CONFIG_EDAC_DEBUG))
		return 0;

	if (!parent)
		return -ENOENT;

	for (i = 0; i < num; i++) {
		ent = edac_debugfs_create_file(attrs[i]->name, attrs[i]->mode,
					       parent, data, &attrs[i]->fops);

		if (!ent)
			break;
	}

	return i;
}