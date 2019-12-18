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
struct dentry {struct dentry* d_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 scalar_t__ d_is_dir (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ simple_positive (struct dentry*) ; 
 int /*<<< orphan*/  simple_rmdir (int /*<<< orphan*/ ,struct dentry*) ; 
 int /*<<< orphan*/  simple_unlink (int /*<<< orphan*/ ,struct dentry*) ; 

__attribute__((used)) static void hypfs_remove(struct dentry *dentry)
{
	struct dentry *parent;

	parent = dentry->d_parent;
	inode_lock(d_inode(parent));
	if (simple_positive(dentry)) {
		if (d_is_dir(dentry))
			simple_rmdir(d_inode(parent), dentry);
		else
			simple_unlink(d_inode(parent), dentry);
	}
	d_drop(dentry);
	dput(dentry);
	inode_unlock(d_inode(parent));
}