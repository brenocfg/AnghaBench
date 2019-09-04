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
typedef  int /*<<< orphan*/  const git_reference ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int GIT_EUNBORNBRANCH ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_reference_is_branch (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_reference_name (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_reference_owner (int /*<<< orphan*/  const*) ; 
 int git_repository_head (int /*<<< orphan*/  const**,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int git_branch_is_head(
		const git_reference *branch)
{
	git_reference *head;
	bool is_same = false;
	int error;

	assert(branch);

	if (!git_reference_is_branch(branch))
		return false;

	error = git_repository_head(&head, git_reference_owner(branch));

	if (error == GIT_EUNBORNBRANCH || error == GIT_ENOTFOUND)
		return false;

	if (error < 0)
		return -1;

	is_same = strcmp(
		git_reference_name(branch),
		git_reference_name(head)) == 0;

	git_reference_free(head);

	return is_same;
}