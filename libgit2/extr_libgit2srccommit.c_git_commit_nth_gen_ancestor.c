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
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ git_commit_dup (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int git_commit_parent (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int git_commit_nth_gen_ancestor(
	git_commit **ancestor,
	const git_commit *commit,
	unsigned int n)
{
	git_commit *current, *parent = NULL;
	int error;

	assert(ancestor && commit);

	if (git_commit_dup(&current, (git_commit *)commit) < 0)
		return -1;

	if (n == 0) {
		*ancestor = current;
		return 0;
	}

	while (n--) {
		error = git_commit_parent(&parent, current, 0);

		git_commit_free(current);

		if (error < 0)
			return error;

		current = parent;
	}

	*ancestor = parent;
	return 0;
}