#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_signature ;
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ git_rebase_operation ;
struct TYPE_6__ {int /*<<< orphan*/  payload; int /*<<< orphan*/  (* signing_cb ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  repo; TYPE_1__ options; int /*<<< orphan*/  current; int /*<<< orphan*/  operations; } ;
typedef  TYPE_3__ git_rebase ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_commit ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int GIT_EAPPLIED ; 
 int /*<<< orphan*/  GIT_ERROR_REBASE ; 
 int GIT_EUNMERGED ; 
 int GIT_OK ; 
 int GIT_PASSTHROUGH ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_2__* git_array_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_contains_nul (int /*<<< orphan*/ *) ; 
 char* git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_is_allocated (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_commit_author (int /*<<< orphan*/ *) ; 
 int git_commit_create_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,char const*,char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const**) ; 
 int git_commit_create_with_signature (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* git_commit_message (int /*<<< orphan*/ *) ; 
 char* git_commit_message_encoding (int /*<<< orphan*/ *) ; 
 int git_commit_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int git_error_set_after_callback_function (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ git_index_has_conflicts (int /*<<< orphan*/ *) ; 
 int git_index_write_tree_to (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ git_oid_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_id (int /*<<< orphan*/ *) ; 
 int git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rebase_commit__create(
	git_commit **out,
	git_rebase *rebase,
	git_index *index,
	git_commit *parent_commit,
	const git_signature *author,
	const git_signature *committer,
	const char *message_encoding,
	const char *message)
{
	git_rebase_operation *operation;
	git_commit *current_commit = NULL, *commit = NULL;
	git_tree *parent_tree = NULL, *tree = NULL;
	git_oid tree_id, commit_id;
	git_buf commit_content = GIT_BUF_INIT, commit_signature = GIT_BUF_INIT,
		signature_field = GIT_BUF_INIT;
	const char *signature_field_string = NULL,
		*commit_signature_string = NULL;
	int error;

	operation = git_array_get(rebase->operations, rebase->current);

	if (git_index_has_conflicts(index)) {
		git_error_set(GIT_ERROR_REBASE, "conflicts have not been resolved");
		error = GIT_EUNMERGED;
		goto done;
	}

	if ((error = git_commit_lookup(&current_commit, rebase->repo, &operation->id)) < 0 ||
		(error = git_commit_tree(&parent_tree, parent_commit)) < 0 ||
		(error = git_index_write_tree_to(&tree_id, index, rebase->repo)) < 0 ||
		(error = git_tree_lookup(&tree, rebase->repo, &tree_id)) < 0)
		goto done;

	if (git_oid_equal(&tree_id, git_tree_id(parent_tree))) {
		git_error_set(GIT_ERROR_REBASE, "this patch has already been applied");
		error = GIT_EAPPLIED;
		goto done;
	}

	if (!author)
		author = git_commit_author(current_commit);

	if (!message) {
		message_encoding = git_commit_message_encoding(current_commit);
		message = git_commit_message(current_commit);
	}

	if ((error = git_commit_create_buffer(&commit_content, rebase->repo, author, committer,
			message_encoding, message, tree, 1, (const git_commit **)&parent_commit)) < 0)
		goto done;

	if (rebase->options.signing_cb) {
		git_error_clear();
		error = git_error_set_after_callback_function(rebase->options.signing_cb(
			&commit_signature, &signature_field, git_buf_cstr(&commit_content),
			rebase->options.payload), "commit signing_cb failed");
		if (error == GIT_PASSTHROUGH) {
			git_buf_dispose(&commit_signature);
			git_buf_dispose(&signature_field);
			git_error_clear();
			error = GIT_OK;
		} else if (error < 0)
			goto done;
	}

	if (git_buf_is_allocated(&commit_signature)) {
		assert(git_buf_contains_nul(&commit_signature));
		commit_signature_string = git_buf_cstr(&commit_signature);
	}

	if (git_buf_is_allocated(&signature_field)) {
		assert(git_buf_contains_nul(&signature_field));
		signature_field_string = git_buf_cstr(&signature_field);
	}

	if ((error = git_commit_create_with_signature(&commit_id, rebase->repo,
			git_buf_cstr(&commit_content), commit_signature_string,
			signature_field_string)))
		goto done;

	if ((error = git_commit_lookup(&commit, rebase->repo, &commit_id)) < 0)
		goto done;

	*out = commit;

done:
	if (error < 0)
		git_commit_free(commit);

	git_buf_dispose(&commit_signature);
	git_buf_dispose(&signature_field);
	git_buf_dispose(&commit_content);
	git_commit_free(current_commit);
	git_tree_free(parent_tree);
	git_tree_free(tree);

	return error;
}