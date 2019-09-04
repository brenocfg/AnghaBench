#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_reference ;
struct TYPE_9__ {int /*<<< orphan*/  checkout_strategy; } ;
typedef  TYPE_1__ git_checkout_options ;
struct TYPE_10__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;
typedef  int /*<<< orphan*/  git_annotated_commit ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_CHECKOUT_FORCE ; 
 TYPE_1__ GIT_CHECKOUT_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_REFS_HEADS_DIR ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_annotated_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_annotated_commit_from_ref (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_clear (TYPE_2__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int /*<<< orphan*/  git_buf_printf (TYPE_2__*,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_checkout_head (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  git_merge (int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_symbolic_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  repo ; 

__attribute__((used)) static int merge_trivial(const char *ours, const char *theirs)
{
	git_buf branch_buf = GIT_BUF_INIT;
	git_checkout_options checkout_opts = GIT_CHECKOUT_OPTIONS_INIT;
	git_reference *our_ref, *their_ref;
	git_annotated_commit *their_heads[1];

	checkout_opts.checkout_strategy = GIT_CHECKOUT_FORCE;

	git_buf_printf(&branch_buf, "%s%s", GIT_REFS_HEADS_DIR, ours);
	cl_git_pass(git_reference_symbolic_create(&our_ref, repo, "HEAD", branch_buf.ptr, 1, NULL));

	cl_git_pass(git_checkout_head(repo, &checkout_opts));

	git_buf_clear(&branch_buf);
	git_buf_printf(&branch_buf, "%s%s", GIT_REFS_HEADS_DIR, theirs);
	cl_git_pass(git_reference_lookup(&their_ref, repo, branch_buf.ptr));
	cl_git_pass(git_annotated_commit_from_ref(&their_heads[0], repo, their_ref));

	cl_git_pass(git_merge(repo, (const git_annotated_commit **)their_heads, 1, NULL, NULL));

	git_buf_dispose(&branch_buf);
	git_reference_free(our_ref);
	git_reference_free(their_ref);
	git_annotated_commit_free(their_heads[0]);

	return 0;
}