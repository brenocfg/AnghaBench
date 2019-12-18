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
 int git_ignore_path_is_ignored (int*,int /*<<< orphan*/ *,char const*) ; 

int git_status_should_ignore(
	int *ignored,
	git_repository *repo,
	const char *path)
{
	return git_ignore_path_is_ignored(ignored, repo, path);
}