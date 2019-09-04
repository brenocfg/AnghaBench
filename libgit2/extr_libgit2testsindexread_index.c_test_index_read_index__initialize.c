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
typedef  int /*<<< orphan*/  git_object ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_RESET_HARD ; 
 int /*<<< orphan*/  _index ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revparse_ext (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 

void test_index_read_index__initialize(void)
{
	git_object *head;
	git_reference *head_ref;

	_repo = cl_git_sandbox_init("testrepo");
	cl_git_pass(git_revparse_ext(&head, &head_ref, _repo, "HEAD"));
	cl_git_pass(git_reset(_repo, head, GIT_RESET_HARD, NULL));
	cl_git_pass(git_repository_index(&_index, _repo));

	git_reference_free(head_ref);
	git_object_free(head);
}