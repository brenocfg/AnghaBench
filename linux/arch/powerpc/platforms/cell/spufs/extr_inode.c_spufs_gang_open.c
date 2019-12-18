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
struct path {int dummy; } ;
struct file {int /*<<< orphan*/ * f_op; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct file*) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int PTR_ERR (struct file*) ; 
 int /*<<< orphan*/  current_cred () ; 
 struct file* dentry_open (struct path*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fd_install (int,struct file*) ; 
 int get_unused_fd_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unused_fd (int) ; 
 int /*<<< orphan*/  simple_dir_operations ; 

__attribute__((used)) static int spufs_gang_open(struct path *path)
{
	int ret;
	struct file *filp;

	ret = get_unused_fd_flags(0);
	if (ret < 0)
		return ret;

	/*
	 * get references for dget and mntget, will be released
	 * in error path of *_open().
	 */
	filp = dentry_open(path, O_RDONLY, current_cred());
	if (IS_ERR(filp)) {
		put_unused_fd(ret);
		return PTR_ERR(filp);
	}

	filp->f_op = &simple_dir_operations;
	fd_install(ret, filp);
	return ret;
}