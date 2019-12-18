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

/* Variables and functions */
 int GIT_PASSTHROUGH ; 
 int /*<<< orphan*/  at_least_one_cb ; 
 int git_reference_foreach_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int repo_contains_no_reference(git_repository *repo)
{
	int error = git_reference_foreach_name(repo, &at_least_one_cb, NULL);

	if (error == GIT_PASSTHROUGH)
		return 0;

	if (!error)
		return 1;

	return error;
}