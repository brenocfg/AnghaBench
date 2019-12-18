#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* path; int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ git_index_entry ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CONFIGMAP_SYMLINKS ; 
 int /*<<< orphan*/  GIT_FILEMODE_LINK ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rewritefile (char*,char*) ; 
 int /*<<< orphan*/  cl_skip () ; 
 int /*<<< orphan*/  g_idx ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_index_add (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* git_index_get_bypath (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository__configmap_lookup (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__ const*,int) ; 

void test_index_bypath__add_honors_symlink(void)
{
	const git_index_entry *entry;
	git_index_entry new_entry;
	int symlinks;

	cl_git_pass(git_repository__configmap_lookup(&symlinks, g_repo, GIT_CONFIGMAP_SYMLINKS));

	if (symlinks)
		cl_skip();

	cl_assert((entry = git_index_get_bypath(g_idx, "README.txt", 0)) != NULL);

	memcpy(&new_entry, entry, sizeof(git_index_entry));
	new_entry.path = "README.txt";
	new_entry.mode = GIT_FILEMODE_LINK;

	cl_git_pass(git_index_add(g_idx, &new_entry));
	cl_git_pass(git_index_write(g_idx));

	cl_git_rewritefile("submod2/README.txt", "Modified but still a (fake) symlink");

	cl_git_pass(git_index_add_bypath(g_idx, "README.txt"));
	cl_git_pass(git_index_write(g_idx));

	cl_assert((entry = git_index_get_bypath(g_idx, "README.txt", 0)) != NULL);
	cl_assert_equal_i(GIT_FILEMODE_LINK, entry->mode);
}