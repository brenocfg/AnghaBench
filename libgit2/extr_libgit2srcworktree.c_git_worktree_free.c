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
struct TYPE_4__ {struct TYPE_4__* name; struct TYPE_4__* parent_path; struct TYPE_4__* gitdir_path; struct TYPE_4__* gitlink_path; struct TYPE_4__* worktree_path; struct TYPE_4__* commondir_path; } ;
typedef  TYPE_1__ git_worktree ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 

void git_worktree_free(git_worktree *wt)
{
	if (!wt)
		return;

	git__free(wt->commondir_path);
	git__free(wt->worktree_path);
	git__free(wt->gitlink_path);
	git__free(wt->gitdir_path);
	git__free(wt->parent_path);
	git__free(wt->name);
	git__free(wt);
}