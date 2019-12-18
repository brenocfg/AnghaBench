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
 int /*<<< orphan*/  GIT_REFS_STASH_FILE ; 
 int git_reference_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char const*) ; 
 int git_reference_ensure_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int update_reflog(
	git_oid *w_commit_oid,
	git_repository *repo,
	const char *message)
{
	git_reference *stash;
	int error;

	if ((error = git_reference_ensure_log(repo, GIT_REFS_STASH_FILE)) < 0)
		return error;

	error = git_reference_create(&stash, repo, GIT_REFS_STASH_FILE, w_commit_oid, 1, message);

	git_reference_free(stash);

	return error;
}