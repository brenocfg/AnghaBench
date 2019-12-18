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
struct dentry {struct dentry* d_fsdata; } ;

/* Variables and functions */
 struct dentry* hypfs_last_dentry ; 
 int /*<<< orphan*/  hypfs_remove (struct dentry*) ; 

__attribute__((used)) static void hypfs_delete_tree(struct dentry *root)
{
	while (hypfs_last_dentry) {
		struct dentry *next_dentry;
		next_dentry = hypfs_last_dentry->d_fsdata;
		hypfs_remove(hypfs_last_dentry);
		hypfs_last_dentry = next_dentry;
	}
}