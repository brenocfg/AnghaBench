#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_7__ {char* path; int /*<<< orphan*/  id; int /*<<< orphan*/  mode; TYPE_1__ member_0; } ;
typedef  TYPE_2__ git_index_entry ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_FILEMODE_BLOB ; 
 int /*<<< orphan*/  cl_assert (TYPE_2__ const*) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,char*) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_repo_get_bool (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  clar__skip () ; 
 int /*<<< orphan*/  g_idx ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_index_add (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* git_index_get_bypath (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 

void test_index_bypath__add_honors_existing_case_3(void)
{
	git_index_entry dummy = { { 0 } };
	const git_index_entry *entry;

	if (!cl_repo_get_bool(g_repo, "core.ignorecase"))
		clar__skip();

	dummy.mode = GIT_FILEMODE_BLOB;
	cl_git_pass(git_oid_fromstr(&dummy.id, "f990a25a74d1a8281ce2ab018ea8df66795cd60b"));

	dummy.path = "just_a_dir/filea.txt";
	cl_git_pass(git_index_add(g_idx, &dummy));

	dummy.path = "Just_A_Dir/fileB.txt";
	cl_git_pass(git_index_add(g_idx, &dummy));

	dummy.path = "just_A_DIR/FILEC.txt";
	cl_git_pass(git_index_add(g_idx, &dummy));

	dummy.path = "Just_a_DIR/FileD.txt";
	cl_git_pass(git_index_add(g_idx, &dummy));

	cl_git_mkfile("submod2/JuSt_A_DiR/fILEE.txt", "This is a file");

	cl_git_pass(git_index_add_bypath(g_idx, "just_a_dir/fILEE.txt"));

	cl_assert(entry = git_index_get_bypath(g_idx, "JUST_A_DIR/fILEE.txt", 0));
	cl_assert_equal_s("just_a_dir/fILEE.txt", entry->path);
}