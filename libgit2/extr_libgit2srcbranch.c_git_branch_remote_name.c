#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t count; char** strings; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ git_strarray ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_remote ;
typedef  int /*<<< orphan*/  git_refspec ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int GIT_EAMBIGUOUS ; 
 int GIT_ENOTFOUND ; 
 int GIT_ERROR ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  GIT_ERROR_REFERENCE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int git_buf_puts (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_buf_sanitize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  git_reference__is_remote (char const*) ; 
 int /*<<< orphan*/ * git_remote__matching_dst_refspec (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int git_remote_list (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int git_remote_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_strarray_free (TYPE_1__*) ; 

int git_branch_remote_name(git_buf *buf, git_repository *repo, const char *refname)
{
	git_strarray remote_list = {0};
	size_t i;
	git_remote *remote;
	const git_refspec *fetchspec;
	int error = 0;
	char *remote_name = NULL;

	assert(buf && repo && refname);

	git_buf_sanitize(buf);

	/* Verify that this is a remote branch */
	if (!git_reference__is_remote(refname)) {
		git_error_set(GIT_ERROR_INVALID, "reference '%s' is not a remote branch.",
			refname);
		error = GIT_ERROR;
		goto cleanup;
	}

	/* Get the remotes */
	if ((error = git_remote_list(&remote_list, repo)) < 0)
		goto cleanup;

	/* Find matching remotes */
	for (i = 0; i < remote_list.count; i++) {
		if ((error = git_remote_lookup(&remote, repo, remote_list.strings[i])) < 0)
			continue;

		fetchspec = git_remote__matching_dst_refspec(remote, refname);
		if (fetchspec) {
			/* If we have not already set out yet, then set
			 * it to the matching remote name. Otherwise
			 * multiple remotes match this reference, and it
			 * is ambiguous. */
			if (!remote_name) {
				remote_name = remote_list.strings[i];
			} else {
				git_remote_free(remote);

				git_error_set(GIT_ERROR_REFERENCE,
					"reference '%s' is ambiguous", refname);
				error = GIT_EAMBIGUOUS;
				goto cleanup;
			}
		}

		git_remote_free(remote);
	}

	if (remote_name) {
		git_buf_clear(buf);
		error = git_buf_puts(buf, remote_name);
	} else {
		git_error_set(GIT_ERROR_REFERENCE,
			"could not determine remote for '%s'", refname);
		error = GIT_ENOTFOUND;
	}

cleanup:
	if (error < 0)
		git_buf_dispose(buf);

	git_strarray_free(&remote_list);
	return error;
}