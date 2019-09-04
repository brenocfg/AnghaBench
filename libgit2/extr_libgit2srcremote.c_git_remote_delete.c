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
 int /*<<< orphan*/  assert (int) ; 
 int remove_branch_config_related_entries (int /*<<< orphan*/ *,char const*) ; 
 int remove_remote_tracking (int /*<<< orphan*/ *,char const*) ; 
 int rename_remote_config_section (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

int git_remote_delete(git_repository *repo, const char *name)
{
	int error;

	assert(repo && name);

	if ((error = remove_branch_config_related_entries(repo, name)) < 0 ||
	    (error = remove_remote_tracking(repo, name)) < 0 ||
	    (error = rename_remote_config_section(repo, name, NULL)) < 0)
		return error;

	return 0;
}