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
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_odb_object ;
typedef  int /*<<< orphan*/  git_odb ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_s (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_commit_create_with_signature (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*,char*) ; 
 int /*<<< orphan*/  git_odb_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_object_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_read (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_odb (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

void test_commit_write__attach_singleline_signature(void)
{
	const char *sig = "magic word: pretty please";

	const char *data =  "tree 6b79e22d69bf46e289df0345a14ca059dfc9bdf6\n\
parent 34734e478d6cf50c27c9d69026d93974d052c454\n\
author Ben Burkert <ben@benburkert.com> 1358451456 -0800\n\
committer Ben Burkert <ben@benburkert.com> 1358451456 -0800\n\
\n\
a simple commit which works\n";

	const char *complete =  "tree 6b79e22d69bf46e289df0345a14ca059dfc9bdf6\n\
parent 34734e478d6cf50c27c9d69026d93974d052c454\n\
author Ben Burkert <ben@benburkert.com> 1358451456 -0800\n\
committer Ben Burkert <ben@benburkert.com> 1358451456 -0800\n\
magicsig magic word: pretty please\n\
\n\
a simple commit which works\n";

	git_oid id;
	git_odb *odb;
	git_odb_object *obj;

	cl_git_pass(git_commit_create_with_signature(&id, g_repo, data, sig, "magicsig"));

	cl_git_pass(git_repository_odb(&odb, g_repo));
	cl_git_pass(git_odb_read(&obj, odb, &id));
	cl_assert_equal_s(complete, git_odb_object_data(obj));

	git_odb_object_free(obj);
	git_odb_free(odb);
}