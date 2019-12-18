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
struct super_block {int dummy; } ;
struct inode {void* i_private; struct file_operations const* i_fop; struct super_block* i_sb; } ;
struct file_operations {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int S_IFREG ; 
 struct dentry* binderfs_create_dentry (struct dentry*,char const*) ; 
 struct inode* binderfs_make_inode (struct super_block*,int) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  fsnotify_create (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 

struct dentry *binderfs_create_file(struct dentry *parent, const char *name,
				    const struct file_operations *fops,
				    void *data)
{
	struct dentry *dentry;
	struct inode *new_inode, *parent_inode;
	struct super_block *sb;

	parent_inode = d_inode(parent);
	inode_lock(parent_inode);

	dentry = binderfs_create_dentry(parent, name);
	if (IS_ERR(dentry))
		goto out;

	sb = parent_inode->i_sb;
	new_inode = binderfs_make_inode(sb, S_IFREG | 0444);
	if (!new_inode) {
		dput(dentry);
		dentry = ERR_PTR(-ENOMEM);
		goto out;
	}

	new_inode->i_fop = fops;
	new_inode->i_private = data;
	d_instantiate(dentry, new_inode);
	fsnotify_create(parent_inode, dentry);

out:
	inode_unlock(parent_inode);
	return dentry;
}