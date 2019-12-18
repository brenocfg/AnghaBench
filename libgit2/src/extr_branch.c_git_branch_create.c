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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int create_branch (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_commit_id (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_oid_tostr_s (int /*<<< orphan*/ ) ; 

int git_branch_create(
	git_reference **ref_out,
	git_repository *repository,
	const char *branch_name,
	const git_commit *commit,
	int force)
{
	return create_branch(ref_out, repository, branch_name, commit, git_oid_tostr_s(git_commit_id(commit)), force);
}