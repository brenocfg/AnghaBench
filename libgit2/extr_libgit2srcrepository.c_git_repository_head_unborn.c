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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_reference ;

/* Variables and functions */
 int GIT_EUNBORNBRANCH ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int git_repository_head (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

int git_repository_head_unborn(git_repository *repo)
{
	git_reference *ref = NULL;
	int error;

	error = git_repository_head(&ref, repo);
	git_reference_free(ref);

	if (error == GIT_EUNBORNBRANCH) {
		git_error_clear();
		return 1;
	}

	if (error < 0)
		return -1;

	return 0;
}