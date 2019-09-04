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
typedef  int /*<<< orphan*/  git_refdb ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_REFCOUNT_INC (int /*<<< orphan*/ *) ; 
 scalar_t__ git_repository_refdb__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

int git_repository_refdb(git_refdb **out, git_repository *repo)
{
	if (git_repository_refdb__weakptr(out, repo) < 0)
		return -1;

	GIT_REFCOUNT_INC(*out);
	return 0;
}