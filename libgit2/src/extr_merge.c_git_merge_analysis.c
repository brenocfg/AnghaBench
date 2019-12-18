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
typedef  int /*<<< orphan*/  git_merge_preference_t ;
typedef  int /*<<< orphan*/  git_merge_analysis_t ;
typedef  int /*<<< orphan*/  git_annotated_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_MERGE ; 
 int /*<<< orphan*/  GIT_HEAD_FILE ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int git_merge_analysis_for_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const**,size_t) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int git_merge_analysis(
	git_merge_analysis_t *analysis_out,
	git_merge_preference_t *preference_out,
	git_repository *repo,
	const git_annotated_commit **their_heads,
	size_t their_heads_len)
{
	git_reference *head_ref = NULL;
	int error = 0;

	if ((error = git_reference_lookup(&head_ref, repo, GIT_HEAD_FILE)) < 0) {
		git_error_set(GIT_ERROR_MERGE, "failed to lookup HEAD reference");
		return error;
	}

	error = git_merge_analysis_for_ref(analysis_out, preference_out, repo, head_ref, their_heads, their_heads_len);

	git_reference_free(head_ref);

	return error;
}