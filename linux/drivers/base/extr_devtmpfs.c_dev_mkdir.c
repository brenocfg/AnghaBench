#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  umode_t ;
struct path {struct dentry* dentry; } ;
struct dentry {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * i_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  LOOKUP_DIRECTORY ; 
 int PTR_ERR (struct dentry*) ; 
 TYPE_1__* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  done_path_create (struct path*,struct dentry*) ; 
 struct dentry* kern_path_create (int /*<<< orphan*/ ,char const*,struct path*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread ; 
 int vfs_mkdir (TYPE_1__*,struct dentry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dev_mkdir(const char *name, umode_t mode)
{
	struct dentry *dentry;
	struct path path;
	int err;

	dentry = kern_path_create(AT_FDCWD, name, &path, LOOKUP_DIRECTORY);
	if (IS_ERR(dentry))
		return PTR_ERR(dentry);

	err = vfs_mkdir(d_inode(path.dentry), dentry, mode);
	if (!err)
		/* mark as kernel-created inode */
		d_inode(dentry)->i_private = &thread;
	done_path_create(&path, dentry);
	return err;
}