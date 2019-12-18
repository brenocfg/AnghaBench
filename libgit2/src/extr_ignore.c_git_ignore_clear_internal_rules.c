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
typedef  int /*<<< orphan*/  git_attr_file ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_IGNORE_DEFAULT_RULES ; 
 int get_internal_ignores (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int git_attr_file__clear_rules (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_attr_file__free (int /*<<< orphan*/ *) ; 
 int parse_ignore_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int git_ignore_clear_internal_rules(git_repository *repo)
{
	int error;
	git_attr_file *ign_internal;

	if ((error = get_internal_ignores(&ign_internal, repo)) < 0)
		return error;

	if (!(error = git_attr_file__clear_rules(ign_internal, true)))
		error = parse_ignore_file(
				repo, ign_internal, GIT_IGNORE_DEFAULT_RULES, false);

	git_attr_file__free(ign_internal);
	return error;
}