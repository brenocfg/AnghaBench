#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  checkout_strategy; } ;
struct TYPE_7__ {TYPE_5__ checkout_opts; int /*<<< orphan*/  merge_opts; int /*<<< orphan*/  mainline; } ;
typedef  TYPE_1__ git_revert_options ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_indexwriter ;
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_commit ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_VERSION (TYPE_1__ const*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GIT_INDEXWRITER_INIT ; 
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int GIT_OID_HEXSZ ; 
 int /*<<< orphan*/  GIT_REVERT_OPTIONS_VERSION ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int git_buf_printf (int /*<<< orphan*/ *,char*,char*,char const*) ; 
 int git_checkout_index (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_id (int /*<<< orphan*/ *) ; 
 char* git_commit_summary (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_indexwriter_cleanup (int /*<<< orphan*/ *) ; 
 int git_indexwriter_commit (int /*<<< orphan*/ *) ; 
 int git_indexwriter_init_for_operation (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_merge__append_conflicts_to_merge_msg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_merge__check_result (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fmt (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int git_reference_peel (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_repository__ensure_not_bare (int /*<<< orphan*/ *,char*) ; 
 int git_repository_head (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int git_revert_commit (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int revert_normalize_opts (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  revert_state_cleanup (int /*<<< orphan*/ *) ; 
 int write_merge_msg (int /*<<< orphan*/ *,char*,char const*) ; 
 int write_revert_head (int /*<<< orphan*/ *,char*) ; 

int git_revert(
	git_repository *repo,
	git_commit *commit,
	const git_revert_options *given_opts)
{
	git_revert_options opts;
	git_reference *our_ref = NULL;
	git_commit *our_commit = NULL;
	char commit_oidstr[GIT_OID_HEXSZ + 1];
	const char *commit_msg;
	git_buf their_label = GIT_BUF_INIT;
	git_index *index = NULL;
	git_indexwriter indexwriter = GIT_INDEXWRITER_INIT;
	int error;

	assert(repo && commit);

	GIT_ERROR_CHECK_VERSION(given_opts, GIT_REVERT_OPTIONS_VERSION, "git_revert_options");

	if ((error = git_repository__ensure_not_bare(repo, "revert")) < 0)
		return error;

	git_oid_fmt(commit_oidstr, git_commit_id(commit));
	commit_oidstr[GIT_OID_HEXSZ] = '\0';

	if ((commit_msg = git_commit_summary(commit)) == NULL) {
		error = -1;
		goto on_error;
	}

	if ((error = git_buf_printf(&their_label, "parent of %.7s... %s", commit_oidstr, commit_msg)) < 0 ||
		(error = revert_normalize_opts(repo, &opts, given_opts, git_buf_cstr(&their_label))) < 0 ||
		(error = git_indexwriter_init_for_operation(&indexwriter, repo, &opts.checkout_opts.checkout_strategy)) < 0 ||
		(error = write_revert_head(repo, commit_oidstr)) < 0 ||
		(error = write_merge_msg(repo, commit_oidstr, commit_msg)) < 0 ||
		(error = git_repository_head(&our_ref, repo)) < 0 ||
		(error = git_reference_peel((git_object **)&our_commit, our_ref, GIT_OBJECT_COMMIT)) < 0 ||
		(error = git_revert_commit(&index, repo, commit, our_commit, opts.mainline, &opts.merge_opts)) < 0 ||
		(error = git_merge__check_result(repo, index)) < 0 ||
		(error = git_merge__append_conflicts_to_merge_msg(repo, index)) < 0 ||
		(error = git_checkout_index(repo, index, &opts.checkout_opts)) < 0 ||
		(error = git_indexwriter_commit(&indexwriter)) < 0)
		goto on_error;

	goto done;

on_error:
	revert_state_cleanup(repo);

done:
	git_indexwriter_cleanup(&indexwriter);
	git_index_free(index);
	git_commit_free(our_commit);
	git_reference_free(our_ref);
	git_buf_dispose(&their_label);

	return error;
}