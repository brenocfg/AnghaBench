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
typedef  int /*<<< orphan*/  git_tree_entry ;
typedef  int /*<<< orphan*/  git_tree ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OID_HEXSZ ; 
 char* git_object_type2string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_tostr (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * git_tree_entry_byindex (int /*<<< orphan*/  const*,size_t) ; 
 int git_tree_entry_filemode (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_tree_entry_id (int /*<<< orphan*/  const*) ; 
 char* git_tree_entry_name (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_tree_entry_type (int /*<<< orphan*/  const*) ; 
 scalar_t__ git_tree_entrycount (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  printf (char*,int,char*,char*,char*) ; 

__attribute__((used)) static void show_tree(const git_tree *tree)
{
	size_t i, max_i = (int)git_tree_entrycount(tree);
	char oidstr[GIT_OID_HEXSZ + 1];
	const git_tree_entry *te;

	for (i = 0; i < max_i; ++i) {
		te = git_tree_entry_byindex(tree, i);

		git_oid_tostr(oidstr, sizeof(oidstr), git_tree_entry_id(te));

		printf("%06o %s %s\t%s\n",
			git_tree_entry_filemode(te),
			git_object_type2string(git_tree_entry_type(te)),
			oidstr, git_tree_entry_name(te));
	}
}