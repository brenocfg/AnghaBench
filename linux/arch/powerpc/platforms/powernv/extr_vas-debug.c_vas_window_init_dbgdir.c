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
struct vas_window {int winid; int /*<<< orphan*/ * dbgname; struct dentry* dbgdir; TYPE_1__* vinst; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dbgdir; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 struct dentry* debugfs_create_dir (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct dentry* debugfs_create_file (char*,int,struct dentry*,struct vas_window*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (struct dentry*) ; 
 int /*<<< orphan*/  hvwc_fops ; 
 int /*<<< orphan*/  info_fops ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ *,int,char*,int) ; 

void vas_window_init_dbgdir(struct vas_window *window)
{
	struct dentry *f, *d;

	if (!window->vinst->dbgdir)
		return;

	window->dbgname = kzalloc(16, GFP_KERNEL);
	if (!window->dbgname)
		return;

	snprintf(window->dbgname, 16, "w%d", window->winid);

	d = debugfs_create_dir(window->dbgname, window->vinst->dbgdir);
	if (IS_ERR(d))
		goto free_name;

	window->dbgdir = d;

	f = debugfs_create_file("info", 0444, d, window, &info_fops);
	if (IS_ERR(f))
		goto remove_dir;

	f = debugfs_create_file("hvwc", 0444, d, window, &hvwc_fops);
	if (IS_ERR(f))
		goto remove_dir;

	return;

remove_dir:
	debugfs_remove_recursive(window->dbgdir);
	window->dbgdir = NULL;

free_name:
	kfree(window->dbgname);
	window->dbgname = NULL;
}