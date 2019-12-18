#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_13__ {int /*<<< orphan*/  symbolic; } ;
struct TYPE_14__ {scalar_t__ type; int /*<<< orphan*/  name; TYPE_1__ target; } ;
typedef  TYPE_2__ git_reference ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_REPOSITORY ; 
 char const* GIT_HEAD_FILE ; 
 scalar_t__ GIT_REFERENCE_SYMBOLIC ; 
 int /*<<< orphan*/  assert (int) ; 
 int checkout_message (int /*<<< orphan*/ *,TYPE_2__*,char const*) ; 
 int detach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ git__strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ git_branch_is_checked_out (TYPE_2__*) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ git_reference__is_branch (char const*) ; 
 int /*<<< orphan*/  git_reference_free (TYPE_2__*) ; 
 scalar_t__ git_reference_is_branch (TYPE_2__*) ; 
 scalar_t__ git_reference_is_remote (TYPE_2__*) ; 
 scalar_t__ git_reference_is_tag (TYPE_2__*) ; 
 int git_reference_lookup (TYPE_2__**,int /*<<< orphan*/ *,char const*) ; 
 char const* git_reference_name (TYPE_2__*) ; 
 int git_reference_symbolic_create (TYPE_2__**,int /*<<< orphan*/ *,char const*,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_target (TYPE_2__*) ; 

int git_repository_set_head(
	git_repository* repo,
	const char* refname)
{
	git_reference *ref = NULL, *current = NULL, *new_head = NULL;
	git_buf log_message = GIT_BUF_INIT;
	int error;

	assert(repo && refname);

	if ((error = git_reference_lookup(&current, repo, GIT_HEAD_FILE)) < 0)
		return error;

	if ((error = checkout_message(&log_message, current, refname)) < 0)
		goto cleanup;

	error = git_reference_lookup(&ref, repo, refname);
	if (error < 0 && error != GIT_ENOTFOUND)
		goto cleanup;

	if (ref && current->type == GIT_REFERENCE_SYMBOLIC && git__strcmp(current->target.symbolic, ref->name) &&
	    git_reference_is_branch(ref) && git_branch_is_checked_out(ref)) {
		git_error_set(GIT_ERROR_REPOSITORY, "cannot set HEAD to reference '%s' as it is the current HEAD "
			"of a linked repository.", git_reference_name(ref));
		error = -1;
		goto cleanup;
	}

	if (!error) {
		if (git_reference_is_branch(ref)) {
			error = git_reference_symbolic_create(&new_head, repo, GIT_HEAD_FILE,
					git_reference_name(ref), true, git_buf_cstr(&log_message));
		} else {
			error = detach(repo, git_reference_target(ref),
				git_reference_is_tag(ref) || git_reference_is_remote(ref) ? refname : NULL);
		}
	} else if (git_reference__is_branch(refname)) {
		error = git_reference_symbolic_create(&new_head, repo, GIT_HEAD_FILE, refname,
				true, git_buf_cstr(&log_message));
	}

cleanup:
	git_buf_dispose(&log_message);
	git_reference_free(current);
	git_reference_free(ref);
	git_reference_free(new_head);
	return error;
}