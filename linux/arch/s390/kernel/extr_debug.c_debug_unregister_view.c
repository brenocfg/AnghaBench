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
struct dentry {int dummy; } ;
struct debug_view {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; struct dentry** debugfs_entries; struct debug_view** views; } ;
typedef  TYPE_1__ debug_info_t ;

/* Variables and functions */
 int DEBUG_MAX_VIEWS ; 
 int /*<<< orphan*/  debugfs_remove (struct dentry*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int debug_unregister_view(debug_info_t *id, struct debug_view *view)
{
	struct dentry *dentry = NULL;
	unsigned long flags;
	int i, rc = 0;

	if (!id)
		goto out;
	spin_lock_irqsave(&id->lock, flags);
	for (i = 0; i < DEBUG_MAX_VIEWS; i++) {
		if (id->views[i] == view)
			break;
	}
	if (i == DEBUG_MAX_VIEWS) {
		rc = -1;
	} else {
		dentry = id->debugfs_entries[i];
		id->views[i] = NULL;
		id->debugfs_entries[i] = NULL;
	}
	spin_unlock_irqrestore(&id->lock, flags);
	debugfs_remove(dentry);
out:
	return rc;
}