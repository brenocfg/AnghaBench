#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int umode_t ;
struct dentry {int dummy; } ;
struct debug_view {int /*<<< orphan*/  name; int /*<<< orphan*/  input_proc; scalar_t__ header_proc; scalar_t__ format_proc; scalar_t__ prolog_proc; } ;
struct TYPE_4__ {int mode; int /*<<< orphan*/  lock; struct dentry** debugfs_entries; struct debug_view** views; int /*<<< orphan*/  name; int /*<<< orphan*/  debugfs_root_entry; } ;
typedef  TYPE_1__ debug_info_t ;

/* Variables and functions */
 int DEBUG_MAX_VIEWS ; 
 int S_IFREG ; 
 int S_IRGRP ; 
 int S_IROTH ; 
 int S_IRUSR ; 
 int S_IWGRP ; 
 int S_IWOTH ; 
 int S_IWUSR ; 
 int S_IXUGO ; 
 int /*<<< orphan*/  debug_file_ops ; 
 struct dentry* debugfs_create_file (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove (struct dentry*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int debug_register_view(debug_info_t *id, struct debug_view *view)
{
	unsigned long flags;
	struct dentry *pde;
	umode_t mode;
	int rc = 0;
	int i;

	if (!id)
		goto out;
	mode = (id->mode | S_IFREG) & ~S_IXUGO;
	if (!(view->prolog_proc || view->format_proc || view->header_proc))
		mode &= ~(S_IRUSR | S_IRGRP | S_IROTH);
	if (!view->input_proc)
		mode &= ~(S_IWUSR | S_IWGRP | S_IWOTH);
	pde = debugfs_create_file(view->name, mode, id->debugfs_root_entry,
				  id, &debug_file_ops);
	spin_lock_irqsave(&id->lock, flags);
	for (i = 0; i < DEBUG_MAX_VIEWS; i++) {
		if (!id->views[i])
			break;
	}
	if (i == DEBUG_MAX_VIEWS) {
		pr_err("Registering view %s/%s would exceed the maximum "
		       "number of views %i\n", id->name, view->name, i);
		rc = -1;
	} else {
		id->views[i] = view;
		id->debugfs_entries[i] = pde;
	}
	spin_unlock_irqrestore(&id->lock, flags);
	if (rc)
		debugfs_remove(pde);
out:
	return rc;
}