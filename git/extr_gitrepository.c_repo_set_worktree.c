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
struct repository {int /*<<< orphan*/  worktree; } ;

/* Variables and functions */
 int /*<<< orphan*/  real_pathdup (char const*,int) ; 
 int /*<<< orphan*/  trace2_def_repo (struct repository*) ; 

void repo_set_worktree(struct repository *repo, const char *path)
{
	repo->worktree = real_pathdup(path, 1);

	trace2_def_repo(repo);
}