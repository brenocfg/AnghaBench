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
struct tree {int entry_fd; scalar_t__ d; int working_dir_fd; int initial_dir_fd; TYPE_1__* stack; int /*<<< orphan*/  restore_time; } ;
struct TYPE_2__ {int flags; int symlink_parent_fd; } ;

/* Variables and functions */
 scalar_t__ INVALID_DIR_HANDLE ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  close_and_restore_time (int,struct tree*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  closedir (scalar_t__) ; 
 int isDirLink ; 
 int /*<<< orphan*/  tree_pop (struct tree*) ; 

__attribute__((used)) static void
tree_close(struct tree *t)
{

	if (t == NULL)
		return;
	if (t->entry_fd >= 0) {
		close_and_restore_time(t->entry_fd, t, &t->restore_time);
		t->entry_fd = -1;
	}
	/* Close the handle of readdir(). */
	if (t->d != INVALID_DIR_HANDLE) {
		closedir(t->d);
		t->d = INVALID_DIR_HANDLE;
	}
	/* Release anything remaining in the stack. */
	while (t->stack != NULL) {
		if (t->stack->flags & isDirLink)
			close(t->stack->symlink_parent_fd);
		tree_pop(t);
	}
	if (t->working_dir_fd >= 0) {
		close(t->working_dir_fd);
		t->working_dir_fd = -1;
	}
	if (t->initial_dir_fd >= 0) {
		close(t->initial_dir_fd);
		t->initial_dir_fd = -1;
	}
}