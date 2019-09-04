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
typedef  int /*<<< orphan*/  git_filter_list ;
typedef  int /*<<< orphan*/  git_buf ;
typedef  int /*<<< orphan*/  git_blob ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_FILTER_DEFAULT ; 
 int /*<<< orphan*/  GIT_FILTER_TO_WORKTREE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ git_blob_is_binary (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_blob_owner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_sanitize (int /*<<< orphan*/ *) ; 
 int git_filter_list_apply_to_blob (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_filter_list_free (int /*<<< orphan*/ *) ; 
 int git_filter_list_load (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int git_blob_filtered_content(
	git_buf *out,
	git_blob *blob,
	const char *path,
	int check_for_binary_data)
{
	int error = 0;
	git_filter_list *fl = NULL;

	assert(blob && path && out);

	git_buf_sanitize(out);

	if (check_for_binary_data && git_blob_is_binary(blob))
		return 0;

	if (!(error = git_filter_list_load(
			&fl, git_blob_owner(blob), blob, path,
			GIT_FILTER_TO_WORKTREE, GIT_FILTER_DEFAULT))) {

		error = git_filter_list_apply_to_blob(out, fl, blob);

		git_filter_list_free(fl);
	}

	return error;
}