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

/* Variables and functions */
 int /*<<< orphan*/  cl_git_fail_with (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_commit_create_with_signature (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*,char*) ; 

void test_commit_write__attach_signature_checks_objects(void)
{
	const char *sig = "magic word: pretty please";
	const char *badtree =  "tree 6b79e22d69bf46e289df0345a14ca059dfc9bdf6\n\
parent 34734e478d6cf50c27c9d69026d93974d052c454\n\
author Ben Burkert <ben@benburkert.com> 1358451456 -0800\n\
committer Ben Burkert <ben@benburkert.com> 1358451456 -0800\n\
\n\
a simple commit which does not work\n";

	const char *badparent =  "tree 4b825dc642cb6eb9a060e54bf8d69288fbee4904\n\
parent 34734e478d6cf50c27c9d69026d93974d052c454\n\
author Ben Burkert <ben@benburkert.com> 1358451456 -0800\n\
committer Ben Burkert <ben@benburkert.com> 1358451456 -0800\n\
\n\
a simple commit which does not work\n";

	git_oid id;

	cl_git_fail_with(-1, git_commit_create_with_signature(&id, g_repo, badtree, sig, "magicsig"));
	cl_git_fail_with(-1, git_commit_create_with_signature(&id, g_repo, badparent, sig, "magicsig"));

}