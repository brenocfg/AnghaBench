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
 int /*<<< orphan*/  GIT_EINVALIDSPEC ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_rename_section (int /*<<< orphan*/ *,char*,char const*) ; 

__attribute__((used)) static void assert_invalid_config_section_name(
	git_repository *repo, const char *name)
{
	cl_git_fail_with(
		git_config_rename_section(repo, "branch.remoteless", name),
		GIT_EINVALIDSPEC);
}