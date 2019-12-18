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
typedef  int /*<<< orphan*/  umode_t ;
struct inode {char* i_private; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; scalar_t__ i_size; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  dget (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  hypfs_file_ops ; 
 struct inode* hypfs_make_inode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inc_nlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (int /*<<< orphan*/ ) ; 
 struct dentry* lookup_one_len (char const*,struct dentry*,scalar_t__) ; 
 int /*<<< orphan*/  simple_dir_inode_operations ; 
 int /*<<< orphan*/  simple_dir_operations ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static struct dentry *hypfs_create_file(struct dentry *parent, const char *name,
					char *data, umode_t mode)
{
	struct dentry *dentry;
	struct inode *inode;

	inode_lock(d_inode(parent));
	dentry = lookup_one_len(name, parent, strlen(name));
	if (IS_ERR(dentry)) {
		dentry = ERR_PTR(-ENOMEM);
		goto fail;
	}
	inode = hypfs_make_inode(parent->d_sb, mode);
	if (!inode) {
		dput(dentry);
		dentry = ERR_PTR(-ENOMEM);
		goto fail;
	}
	if (S_ISREG(mode)) {
		inode->i_fop = &hypfs_file_ops;
		if (data)
			inode->i_size = strlen(data);
		else
			inode->i_size = 0;
	} else if (S_ISDIR(mode)) {
		inode->i_op = &simple_dir_inode_operations;
		inode->i_fop = &simple_dir_operations;
		inc_nlink(d_inode(parent));
	} else
		BUG();
	inode->i_private = data;
	d_instantiate(dentry, inode);
	dget(dentry);
fail:
	inode_unlock(d_inode(parent));
	return dentry;
}