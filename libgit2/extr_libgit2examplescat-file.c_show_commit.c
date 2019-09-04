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
typedef  int /*<<< orphan*/  oidstr ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OID_HEXSZ ; 
 int /*<<< orphan*/  git_commit_author (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_commit_committer (int /*<<< orphan*/  const*) ; 
 char* git_commit_message (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_commit_parent_id (int /*<<< orphan*/  const*,unsigned int) ; 
 scalar_t__ git_commit_parentcount (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_commit_tree_id (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_oid_tostr (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_signature (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static void show_commit(const git_commit *commit)
{
	unsigned int i, max_i;
	char oidstr[GIT_OID_HEXSZ + 1];

	git_oid_tostr(oidstr, sizeof(oidstr), git_commit_tree_id(commit));
	printf("tree %s\n", oidstr);

	max_i = (unsigned int)git_commit_parentcount(commit);
	for (i = 0; i < max_i; ++i) {
		git_oid_tostr(oidstr, sizeof(oidstr), git_commit_parent_id(commit, i));
		printf("parent %s\n", oidstr);
	}

	print_signature("author", git_commit_author(commit));
	print_signature("committer", git_commit_committer(commit));

	if (git_commit_message(commit))
		printf("\n%s\n", git_commit_message(commit));
}