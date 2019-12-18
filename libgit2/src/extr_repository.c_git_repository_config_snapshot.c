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
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int git_config_snapshot (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int git_repository_config__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

int git_repository_config_snapshot(git_config **out, git_repository *repo)
{
	int error;
	git_config *weak;

	if ((error = git_repository_config__weakptr(&weak, repo)) < 0)
		return error;

	return git_config_snapshot(out, weak);
}