#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_reference ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_ERROR_REFERENCE ; 
 char* GIT_REFS_HEADS_DIR ; 
 char* GIT_REFS_REMOTES_DIR ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int git_buf_joinpath (TYPE_1__*,char*,char const*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char*,char const*) ; 
 int git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int retrieve_branch_reference(
	git_reference **branch_reference_out,
	git_repository *repo,
	const char *branch_name,
	bool is_remote)
{
	git_reference *branch = NULL;
	int error = 0;
	char *prefix;
	git_buf ref_name = GIT_BUF_INIT;

	prefix = is_remote ? GIT_REFS_REMOTES_DIR : GIT_REFS_HEADS_DIR;

	if ((error = git_buf_joinpath(&ref_name, prefix, branch_name)) < 0)
		/* OOM */;
	else if ((error = git_reference_lookup(&branch, repo, ref_name.ptr)) < 0)
		git_error_set(
			GIT_ERROR_REFERENCE, "cannot locate %s branch '%s'",
			is_remote ? "remote-tracking" : "local", branch_name);

	*branch_reference_out = branch; /* will be NULL on error */

	git_buf_dispose(&ref_name);
	return error;
}