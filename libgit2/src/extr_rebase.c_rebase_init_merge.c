#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {int /*<<< orphan*/  gitdir; } ;
typedef  TYPE_2__ git_repository ;
typedef  int /*<<< orphan*/  git_reference ;
struct TYPE_23__ {int /*<<< orphan*/  checkout_options; int /*<<< orphan*/  quiet; } ;
struct TYPE_25__ {int head_detached; TYPE_1__ options; int /*<<< orphan*/  onto_id; int /*<<< orphan*/  orig_head_id; int /*<<< orphan*/  quiet; void* onto_name; void* orig_head_name; void* state_path; } ;
typedef  TYPE_3__ git_rebase ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_commit ;
struct TYPE_26__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_4__ git_buf ;
struct TYPE_27__ {scalar_t__ ref_name; } ;
typedef  TYPE_5__ git_annotated_commit ;

/* Variables and functions */
 TYPE_4__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (void*) ; 
 int /*<<< orphan*/  GIT_HEAD_FILE ; 
 int /*<<< orphan*/  GIT_UNUSED (TYPE_5__ const*) ; 
 int /*<<< orphan*/  REBASE_MERGE_DIR ; 
 void* git__strdup (scalar_t__) ; 
 int /*<<< orphan*/  git_annotated_commit_id (TYPE_5__ const*) ; 
 void* git_buf_detach (TYPE_4__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_4__*) ; 
 int git_buf_joinpath (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int git_buf_printf (TYPE_4__*,char*,scalar_t__) ; 
 int git_checkout_tree (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int git_commit_lookup (int /*<<< orphan*/ **,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_reference_create (int /*<<< orphan*/ **,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 scalar_t__ rebase_onto_name (TYPE_5__ const*) ; 
 int rebase_setupfiles (TYPE_3__*) ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 

__attribute__((used)) static int rebase_init_merge(
	git_rebase *rebase,
	git_repository *repo,
	const git_annotated_commit *branch,
	const git_annotated_commit *upstream,
	const git_annotated_commit *onto)
{
	git_reference *head_ref = NULL;
	git_commit *onto_commit = NULL;
	git_buf reflog = GIT_BUF_INIT;
	git_buf state_path = GIT_BUF_INIT;
	int error;

	GIT_UNUSED(upstream);

	if ((error = git_buf_joinpath(&state_path, repo->gitdir, REBASE_MERGE_DIR)) < 0)
		goto done;

	rebase->state_path = git_buf_detach(&state_path);
	GIT_ERROR_CHECK_ALLOC(rebase->state_path);

	if (branch->ref_name && strcmp(branch->ref_name, "HEAD")) {
		rebase->orig_head_name = git__strdup(branch->ref_name);
		GIT_ERROR_CHECK_ALLOC(rebase->orig_head_name);
	} else {
		rebase->head_detached = 1;
	}

	rebase->onto_name = git__strdup(rebase_onto_name(onto));
	GIT_ERROR_CHECK_ALLOC(rebase->onto_name);

	rebase->quiet = rebase->options.quiet;

	git_oid_cpy(&rebase->orig_head_id, git_annotated_commit_id(branch));
	git_oid_cpy(&rebase->onto_id, git_annotated_commit_id(onto));

	if ((error = rebase_setupfiles(rebase)) < 0 ||
		(error = git_buf_printf(&reflog,
			"rebase: checkout %s", rebase_onto_name(onto))) < 0 ||
		(error = git_commit_lookup(
			&onto_commit, repo, git_annotated_commit_id(onto))) < 0 ||
		(error = git_checkout_tree(repo,
			(git_object *)onto_commit, &rebase->options.checkout_options)) < 0 ||
		(error = git_reference_create(&head_ref, repo, GIT_HEAD_FILE,
			git_annotated_commit_id(onto), 1, reflog.ptr)) < 0)
		goto done;

done:
	git_reference_free(head_ref);
	git_commit_free(onto_commit);
	git_buf_dispose(&reflog);
	git_buf_dispose(&state_path);

	return error;
}