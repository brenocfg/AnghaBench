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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_describe_result ;
struct TYPE_4__ {int show_commit_oid_as_fallback; } ;
typedef  TYPE_1__ git_describe_options ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 TYPE_1__ GIT_DESCRIBE_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_cleanup () ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  delete_cb ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_describe_commit (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_describe_result_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 

void test_describe_describe__describe_a_repo_with_no_refs(void)
{
	git_repository *repo;
	git_describe_options opts = GIT_DESCRIBE_OPTIONS_INIT;
	git_buf buf = GIT_BUF_INIT;
	git_object *object;
	git_describe_result *result = NULL;

	repo = cl_git_sandbox_init("testrepo.git");
	cl_git_pass(git_revparse_single(&object, repo, "HEAD"));

	cl_git_pass(git_reference_foreach(repo, delete_cb, NULL));

	/* Impossible to describe without falling back to OIDs */
	cl_git_fail(git_describe_commit(&result, object, &opts));

	/* Try again with OID fallbacks */
	opts.show_commit_oid_as_fallback = 1;
	cl_git_pass(git_describe_commit(&result, object, &opts));

	git_describe_result_free(result);
	git_object_free(object);
	git_buf_dispose(&buf);
	cl_git_sandbox_cleanup();
}