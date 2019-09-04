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
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_merge_preference_t ;
typedef  int /*<<< orphan*/  git_merge_analysis_t ;
typedef  int /*<<< orphan*/  git_buf ;
typedef  int /*<<< orphan*/  git_annotated_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_HEAD_FILE ; 
 int /*<<< orphan*/  GIT_REFS_HEADS_DIR ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_annotated_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_annotated_commit_from_ref (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_merge_analysis_for_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo ; 

__attribute__((used)) static void analysis_from_branch(
	git_merge_analysis_t *merge_analysis,
	git_merge_preference_t *merge_pref,
	const char *our_branchname,
	const char *their_branchname)
{
	git_buf our_refname = GIT_BUF_INIT;
	git_buf their_refname = GIT_BUF_INIT;
	git_reference *our_ref;
	git_reference *their_ref;
	git_annotated_commit *their_head;

	if (our_branchname != NULL) {
		cl_git_pass(git_buf_printf(&our_refname, "%s%s", GIT_REFS_HEADS_DIR, our_branchname));
		cl_git_pass(git_reference_lookup(&our_ref, repo, git_buf_cstr(&our_refname)));
	} else {
		cl_git_pass(git_reference_lookup(&our_ref, repo, GIT_HEAD_FILE));
	}

	cl_git_pass(git_buf_printf(&their_refname, "%s%s", GIT_REFS_HEADS_DIR, their_branchname));

	cl_git_pass(git_reference_lookup(&their_ref, repo, git_buf_cstr(&their_refname)));
	cl_git_pass(git_annotated_commit_from_ref(&their_head, repo, their_ref));

	cl_git_pass(git_merge_analysis_for_ref(merge_analysis, merge_pref, repo, our_ref, (const git_annotated_commit **)&their_head, 1));

	git_buf_dispose(&our_refname);
	git_buf_dispose(&their_refname);
	git_annotated_commit_free(their_head);
	git_reference_free(our_ref);
	git_reference_free(their_ref);
}