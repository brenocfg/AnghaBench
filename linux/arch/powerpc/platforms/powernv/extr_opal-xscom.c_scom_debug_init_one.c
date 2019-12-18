#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct scom_debug_entry* data; int /*<<< orphan*/  size; } ;
struct scom_debug_entry {int chip; TYPE_1__ path; int /*<<< orphan*/  name; } ;
struct device_node {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  debugfs_create_blob (char*,int,struct dentry*,TYPE_1__*) ; 
 struct dentry* debugfs_create_dir (int /*<<< orphan*/ ,struct dentry*) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,struct dentry*,struct scom_debug_entry*,int /*<<< orphan*/ *) ; 
 scalar_t__ kasprintf (int /*<<< orphan*/ ,char*,struct device_node*) ; 
 int /*<<< orphan*/  kfree (struct scom_debug_entry*) ; 
 struct scom_debug_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scom_debug_fops ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int scom_debug_init_one(struct dentry *root, struct device_node *dn,
			       int chip)
{
	struct scom_debug_entry *ent;
	struct dentry *dir;

	ent = kzalloc(sizeof(*ent), GFP_KERNEL);
	if (!ent)
		return -ENOMEM;

	ent->chip = chip;
	snprintf(ent->name, 16, "%08x", chip);
	ent->path.data = (void *)kasprintf(GFP_KERNEL, "%pOF", dn);
	ent->path.size = strlen((char *)ent->path.data);

	dir = debugfs_create_dir(ent->name, root);
	if (!dir) {
		kfree(ent->path.data);
		kfree(ent);
		return -1;
	}

	debugfs_create_blob("devspec", 0400, dir, &ent->path);
	debugfs_create_file("access", 0600, dir, ent, &scom_debug_fops);

	return 0;
}