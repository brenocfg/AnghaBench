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
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int GIT_EEXISTS ; 
 int /*<<< orphan*/  GIT_REFS_HEADS_DIR ; 
 int create_tracking_branch (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,char const*,char const*) ; 
 int /*<<< orphan*/  git__prefixcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_name (int /*<<< orphan*/ *) ; 
 int git_repository_set_head (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int update_head_to_new_branch(
	git_repository *repo,
	const git_oid *target,
	const char *name,
	const char *reflog_message)
{
	git_reference *tracking_branch = NULL;
	int error;

	if (!git__prefixcmp(name, GIT_REFS_HEADS_DIR))
		name += strlen(GIT_REFS_HEADS_DIR);

	error = create_tracking_branch(&tracking_branch, repo, target, name,
			reflog_message);

	if (!error)
		error = git_repository_set_head(
			repo, git_reference_name(tracking_branch));

	git_reference_free(tracking_branch);

	/* if it already existed, then the user's refspec created it for us, ignore it' */
	if (error == GIT_EEXISTS)
		error = 0;

	return error;
}