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
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clar__assert (int /*<<< orphan*/ ,char const*,int,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  repo ; 

__attribute__((used)) static void assert_commit_is_head_(git_commit *c, const char *file, int line)
{
	git_commit *head;
	cl_git_pass(git_revparse_single((git_object **)&head, repo, "HEAD"));
	clar__assert(git_oid_equal(git_commit_id(c), git_commit_id(head)), file, line, "Commit is not the HEAD", NULL, 1);
	git_commit_free(head);
}