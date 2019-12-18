#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_reference ;
struct TYPE_7__ {int /*<<< orphan*/  orig_head_name; int /*<<< orphan*/  repo; int /*<<< orphan*/  orig_head_id; int /*<<< orphan*/  onto_id; } ;
typedef  TYPE_1__ git_rebase ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_commit ;
struct TYPE_8__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_HEAD_FILE ; 
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int GIT_OID_HEXSZ ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int git_buf_printf (TYPE_2__*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fmt (char*,int /*<<< orphan*/ *) ; 
 int git_reference_create_matching (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int git_reference_peel (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_reference_symbolic_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int git_repository_head (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int return_to_orig_head(git_rebase *rebase)
{
	git_reference *terminal_ref = NULL, *branch_ref = NULL, *head_ref = NULL;
	git_commit *terminal_commit = NULL;
	git_buf branch_msg = GIT_BUF_INIT, head_msg = GIT_BUF_INIT;
	char onto[GIT_OID_HEXSZ];
	int error = 0;

	git_oid_fmt(onto, &rebase->onto_id);

	if ((error = git_buf_printf(&branch_msg,
			"rebase finished: %s onto %.*s",
			rebase->orig_head_name, GIT_OID_HEXSZ, onto)) == 0 &&
		(error = git_buf_printf(&head_msg,
			"rebase finished: returning to %s",
			rebase->orig_head_name)) == 0 &&
		(error = git_repository_head(&terminal_ref, rebase->repo)) == 0 &&
		(error = git_reference_peel((git_object **)&terminal_commit,
			terminal_ref, GIT_OBJECT_COMMIT)) == 0 &&
		(error = git_reference_create_matching(&branch_ref,
			rebase->repo, rebase->orig_head_name,
			git_commit_id(terminal_commit), 1,
			&rebase->orig_head_id, branch_msg.ptr)) == 0)
		error = git_reference_symbolic_create(&head_ref,
			rebase->repo, GIT_HEAD_FILE, rebase->orig_head_name, 1,
			head_msg.ptr);

	git_buf_dispose(&head_msg);
	git_buf_dispose(&branch_msg);
	git_commit_free(terminal_commit);
	git_reference_free(head_ref);
	git_reference_free(branch_ref);
	git_reference_free(terminal_ref);

	return error;
}