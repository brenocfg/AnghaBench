#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_commit ;
struct TYPE_7__ {int /*<<< orphan*/  perfdata_cb; int /*<<< orphan*/  progress_cb; int /*<<< orphan*/  checkout_strategy; } ;
typedef  TYPE_1__ git_checkout_options ;
typedef  int /*<<< orphan*/  git_annotated_commit ;
struct TYPE_8__ {scalar_t__ perf; scalar_t__ progress; scalar_t__ force; } ;
typedef  TYPE_2__ checkout_options ;
struct TYPE_9__ {char* message; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CHECKOUT_FORCE ; 
 TYPE_1__ GIT_CHECKOUT_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_CHECKOUT_SAFE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  git_annotated_commit_id (int /*<<< orphan*/ *) ; 
 scalar_t__ git_annotated_commit_ref (int /*<<< orphan*/ *) ; 
 int git_checkout_tree (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_1__*) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_4__* git_error_last () ; 
 int git_repository_set_head (int /*<<< orphan*/ *,scalar_t__) ; 
 int git_repository_set_head_detached_from_annotated (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_checkout_progress ; 
 int /*<<< orphan*/  print_perf_data ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int perform_checkout_ref(git_repository *repo, git_annotated_commit *target, checkout_options *opts)
{
	git_checkout_options checkout_opts = GIT_CHECKOUT_OPTIONS_INIT;
	git_commit *target_commit = NULL;
	int err;

	/** Setup our checkout options from the parsed options */
	checkout_opts.checkout_strategy = GIT_CHECKOUT_SAFE;
	if (opts->force)
		checkout_opts.checkout_strategy = GIT_CHECKOUT_FORCE;

	if (opts->progress)
		checkout_opts.progress_cb = print_checkout_progress;

	if (opts->perf)
		checkout_opts.perfdata_cb = print_perf_data;

	/** Grab the commit we're interested to move to */
	err = git_commit_lookup(&target_commit, repo, git_annotated_commit_id(target));
	if (err != 0) {
		fprintf(stderr, "failed to lookup commit: %s\n", git_error_last()->message);
		goto cleanup;
	}

	/**
	 * Perform the checkout so the workdir corresponds to what target_commit
	 * contains.
	 *
	 * Note that it's okay to pass a git_commit here, because it will be
	 * peeled to a tree.
	 */
	err = git_checkout_tree(repo, (const git_object *)target_commit, &checkout_opts);
	if (err != 0) {
		fprintf(stderr, "failed to checkout tree: %s\n", git_error_last()->message);
		goto cleanup;
	}

	/**
	 * Now that the checkout has completed, we have to update HEAD.
	 *
	 * Depending on the "origin" of target (ie. it's an OID or a branch name),
	 * we might need to detach HEAD.
	 */
	if (git_annotated_commit_ref(target)) {
		err = git_repository_set_head(repo, git_annotated_commit_ref(target));
	} else {
		err = git_repository_set_head_detached_from_annotated(repo, target);
	}
	if (err != 0) {
		fprintf(stderr, "failed to update HEAD reference: %s\n", git_error_last()->message);
		goto cleanup;
	}

cleanup:
	git_commit_free(target_commit);

	return err;
}