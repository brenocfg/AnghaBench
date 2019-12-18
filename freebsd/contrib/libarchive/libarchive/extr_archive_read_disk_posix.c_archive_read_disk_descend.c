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
struct TYPE_7__ {int /*<<< orphan*/  st_ino; int /*<<< orphan*/  st_dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  st_ino; int /*<<< orphan*/  st_dev; } ;
struct tree {scalar_t__ visit_type; scalar_t__ descend; TYPE_4__* stack; int /*<<< orphan*/  restore_time; TYPE_3__ st; int /*<<< orphan*/  current_filesystem_id; int /*<<< orphan*/  basename; TYPE_1__ lst; } ;
struct archive_read_disk {struct tree* tree; } ;
struct archive {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  flags; TYPE_2__* parent; } ;
struct TYPE_6__ {int /*<<< orphan*/ * parent; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ARCHIVE_READ_DISK_MAGIC ; 
 int ARCHIVE_STATE_DATA ; 
 int ARCHIVE_STATE_HEADER ; 
 scalar_t__ TREE_REGULAR ; 
 int /*<<< orphan*/  archive_check_magic (struct archive*,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  isDir ; 
 int /*<<< orphan*/  isDirLink ; 
 scalar_t__ tree_current_is_dir (struct tree*) ; 
 scalar_t__ tree_current_is_physical_dir (struct tree*) ; 
 int /*<<< orphan*/  tree_push (struct tree*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
archive_read_disk_descend(struct archive *_a)
{
	struct archive_read_disk *a = (struct archive_read_disk *)_a;
	struct tree *t = a->tree;

	archive_check_magic(_a, ARCHIVE_READ_DISK_MAGIC,
	    ARCHIVE_STATE_HEADER | ARCHIVE_STATE_DATA,
	    "archive_read_disk_descend");

	if (t->visit_type != TREE_REGULAR || !t->descend)
		return (ARCHIVE_OK);

	/*
	 * We must not treat the initial specified path as a physical dir,
	 * because if we do then we will try and ascend out of it by opening
	 * ".." which is (a) wrong and (b) causes spurious permissions errors
	 * if ".." is not readable by us. Instead, treat it as if it were a
	 * symlink. (This uses an extra fd, but it can only happen once at the
	 * top level of a traverse.) But we can't necessarily assume t->st is
	 * valid here (though t->lst is), which complicates the logic a
	 * little.
	 */
	if (tree_current_is_physical_dir(t)) {
		tree_push(t, t->basename, t->current_filesystem_id,
		    t->lst.st_dev, t->lst.st_ino, &t->restore_time);
		if (t->stack->parent->parent != NULL)
			t->stack->flags |= isDir;
		else
			t->stack->flags |= isDirLink;
	} else if (tree_current_is_dir(t)) {
		tree_push(t, t->basename, t->current_filesystem_id,
		    t->st.st_dev, t->st.st_ino, &t->restore_time);
		t->stack->flags |= isDirLink;
	}
	t->descend = 0;
	return (ARCHIVE_OK);
}