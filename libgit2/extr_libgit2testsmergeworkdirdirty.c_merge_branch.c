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
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_merge_options ;
struct TYPE_4__ {int /*<<< orphan*/  checkout_strategy; } ;
typedef  TYPE_1__ git_checkout_options ;
typedef  int /*<<< orphan*/  git_annotated_commit ;

/* Variables and functions */
 TYPE_1__ GIT_CHECKOUT_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_CHECKOUT_SAFE ; 
 int /*<<< orphan*/  GIT_MERGE_OPTIONS_INIT ; 
 int /*<<< orphan*/  MERGE_BRANCH_OID ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_annotated_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_annotated_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int git_merge (int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo ; 

__attribute__((used)) static int merge_branch(void)
{
	git_oid their_oids[1];
	git_annotated_commit *their_head;
	git_merge_options merge_opts = GIT_MERGE_OPTIONS_INIT;
	git_checkout_options checkout_opts = GIT_CHECKOUT_OPTIONS_INIT;
	int error;

	cl_git_pass(git_oid_fromstr(&their_oids[0], MERGE_BRANCH_OID));
	cl_git_pass(git_annotated_commit_lookup(&their_head, repo, &their_oids[0]));

	checkout_opts.checkout_strategy = GIT_CHECKOUT_SAFE;
	error = git_merge(repo, (const git_annotated_commit **)&their_head, 1, &merge_opts, &checkout_opts);

	git_annotated_commit_free(their_head);

	return error;
}