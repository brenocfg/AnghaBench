#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  tn_dirhead; } ;
struct tmpfs_node {TYPE_2__ tn_dir; } ;
struct TYPE_7__ {int /*<<< orphan*/  td_duphead; } ;
struct tmpfs_dirent {TYPE_3__ ud; } ;
struct tmpfs_dir_cursor {struct tmpfs_dirent* tdc_current; struct tmpfs_dirent* tdc_tree; } ;
struct TYPE_5__ {int /*<<< orphan*/  entries; } ;
struct TYPE_8__ {TYPE_1__ td_dup; } ;

/* Variables and functions */
 struct tmpfs_dirent* LIST_FIRST (int /*<<< orphan*/ *) ; 
 struct tmpfs_dirent* LIST_NEXT (struct tmpfs_dirent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 struct tmpfs_dirent* RB_NEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct tmpfs_dirent*) ; 
 int /*<<< orphan*/  tmpfs_dir ; 
 scalar_t__ tmpfs_dirent_dup (struct tmpfs_dirent*) ; 
 scalar_t__ tmpfs_dirent_duphead (struct tmpfs_dirent*) ; 
 TYPE_4__ uh ; 

struct tmpfs_dirent *
tmpfs_dir_next(struct tmpfs_node *dnode, struct tmpfs_dir_cursor *dc)
{
	struct tmpfs_dirent *de;

	MPASS(dc->tdc_tree != NULL);
	if (tmpfs_dirent_dup(dc->tdc_current)) {
		dc->tdc_current = LIST_NEXT(dc->tdc_current, uh.td_dup.entries);
		if (dc->tdc_current != NULL)
			return (dc->tdc_current);
	}
	dc->tdc_tree = dc->tdc_current = RB_NEXT(tmpfs_dir,
	    &dnode->tn_dir.tn_dirhead, dc->tdc_tree);
	if ((de = dc->tdc_current) != NULL && tmpfs_dirent_duphead(de)) {
		dc->tdc_current = LIST_FIRST(&de->ud.td_duphead);
		MPASS(dc->tdc_current != NULL);
	}

	return (dc->tdc_current);
}