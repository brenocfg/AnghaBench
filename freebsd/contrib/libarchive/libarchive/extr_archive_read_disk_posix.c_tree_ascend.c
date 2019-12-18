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
struct tree_entry {int flags; int symlink_parent_fd; int /*<<< orphan*/  restore_time; } ;
struct tree {int working_dir_fd; int /*<<< orphan*/  depth; int /*<<< orphan*/  openCount; int /*<<< orphan*/  flags; int /*<<< orphan*/  tree_errno; struct tree_entry* stack; } ;

/* Variables and functions */
 int O_CLOEXEC ; 
 int O_RDONLY ; 
 int TREE_ERROR_FATAL ; 
 int /*<<< orphan*/  __archive_ensure_cloexec_flag (int) ; 
 int /*<<< orphan*/  close_and_restore_time (int,struct tree*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int isDirLink ; 
 int /*<<< orphan*/  onWorkingDir ; 
 int open_on_current_dir (struct tree*,char*,int) ; 

__attribute__((used)) static int
tree_ascend(struct tree *t)
{
	struct tree_entry *te;
	int new_fd, r = 0, prev_dir_fd;

	te = t->stack;
	prev_dir_fd = t->working_dir_fd;
	if (te->flags & isDirLink)
		new_fd = te->symlink_parent_fd;
	else {
		new_fd = open_on_current_dir(t, "..", O_RDONLY | O_CLOEXEC);
		__archive_ensure_cloexec_flag(new_fd);
	}
	if (new_fd < 0) {
		t->tree_errno = errno;
		r = TREE_ERROR_FATAL;
	} else {
		/* Renew the current working directory. */
		t->working_dir_fd = new_fd;
		t->flags &= ~onWorkingDir;
		/* Current directory has been changed, we should
		 * close an fd of previous working directory. */
		close_and_restore_time(prev_dir_fd, t, &te->restore_time);
		if (te->flags & isDirLink) {
			t->openCount--;
			te->symlink_parent_fd = -1;
		}
		t->depth--;
	}
	return (r);
}