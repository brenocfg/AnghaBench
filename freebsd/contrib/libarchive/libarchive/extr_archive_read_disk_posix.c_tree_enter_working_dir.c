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
struct tree {scalar_t__ depth; int flags; int /*<<< orphan*/  working_dir_fd; } ;

/* Variables and functions */
 int fchdir (int /*<<< orphan*/ ) ; 
 int onInitialDir ; 
 int onWorkingDir ; 

__attribute__((used)) static int
tree_enter_working_dir(struct tree *t)
{
	int r = 0;

	/*
	 * Change the current directory if really needed.
	 * Sometimes this is unneeded when we did not do
	 * descent.
	 */
	if (t->depth > 0 && (t->flags & onWorkingDir) == 0) {
		r = fchdir(t->working_dir_fd);
		if (r == 0) {
			t->flags &= ~onInitialDir;
			t->flags |= onWorkingDir;
		}
	}
	return (r);
}