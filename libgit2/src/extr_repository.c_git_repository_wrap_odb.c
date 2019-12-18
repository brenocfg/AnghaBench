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
typedef  int /*<<< orphan*/  git_odb ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_set_odb (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * repository_alloc () ; 

int git_repository_wrap_odb(git_repository **repo_out, git_odb *odb)
{
	git_repository *repo;

	repo = repository_alloc();
	GIT_ERROR_CHECK_ALLOC(repo);

	git_repository_set_odb(repo, odb);
	*repo_out = repo;

	return 0;
}