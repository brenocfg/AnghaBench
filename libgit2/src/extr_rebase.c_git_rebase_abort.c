#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_reference ;
struct TYPE_6__ {int /*<<< orphan*/  checkout_options; } ;
struct TYPE_7__ {TYPE_1__ options; int /*<<< orphan*/  repo; int /*<<< orphan*/  orig_head_id; int /*<<< orphan*/  orig_head_name; scalar_t__ head_detached; scalar_t__ inmemory; } ;
typedef  TYPE_2__ git_rebase ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_HEAD_FILE ; 
 int /*<<< orphan*/  GIT_RESET_HARD ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int git_reference_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int git_reference_symbolic_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int git_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int rebase_cleanup (TYPE_2__*) ; 

int git_rebase_abort(git_rebase *rebase)
{
	git_reference *orig_head_ref = NULL;
	git_commit *orig_head_commit = NULL;
	int error;

	assert(rebase);

	if (rebase->inmemory)
		return 0;

	error = rebase->head_detached ?
		git_reference_create(&orig_head_ref, rebase->repo, GIT_HEAD_FILE,
			 &rebase->orig_head_id, 1, "rebase: aborting") :
		git_reference_symbolic_create(
			&orig_head_ref, rebase->repo, GIT_HEAD_FILE, rebase->orig_head_name, 1,
			"rebase: aborting");

	if (error < 0)
		goto done;

	if ((error = git_commit_lookup(
			&orig_head_commit, rebase->repo, &rebase->orig_head_id)) < 0 ||
		(error = git_reset(rebase->repo, (git_object *)orig_head_commit,
			GIT_RESET_HARD, &rebase->options.checkout_options)) < 0)
		goto done;

	error = rebase_cleanup(rebase);

done:
	git_commit_free(orig_head_commit);
	git_reference_free(orig_head_ref);

	return error;
}