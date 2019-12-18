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
struct inode {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_delete (struct dentry*) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dget (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 scalar_t__ simple_positive (struct dentry*) ; 
 int /*<<< orphan*/  simple_unlink (struct inode*,struct dentry*) ; 

void binderfs_remove_file(struct dentry *dentry)
{
	struct inode *parent_inode;

	parent_inode = d_inode(dentry->d_parent);
	inode_lock(parent_inode);
	if (simple_positive(dentry)) {
		dget(dentry);
		simple_unlink(parent_inode, dentry);
		d_delete(dentry);
		dput(dentry);
	}
	inode_unlock(parent_inode);
}