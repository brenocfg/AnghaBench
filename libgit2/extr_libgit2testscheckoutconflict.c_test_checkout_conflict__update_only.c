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
struct checkout_index_entry {int member_0; int member_2; char* member_3; int /*<<< orphan*/  member_1; } ;
struct TYPE_4__ {int /*<<< orphan*/  checkout_strategy; } ;
typedef  TYPE_1__ git_checkout_options ;

/* Variables and functions */
 int /*<<< orphan*/  AUTOMERGEABLE_ANCESTOR_OID ; 
 int /*<<< orphan*/  AUTOMERGEABLE_MERGED_FILE ; 
 int /*<<< orphan*/  AUTOMERGEABLE_OURS_OID ; 
 int /*<<< orphan*/  AUTOMERGEABLE_THEIRS_OID ; 
 int /*<<< orphan*/  CONFLICTING_ANCESTOR_OID ; 
 int /*<<< orphan*/  CONFLICTING_OURS_FILE ; 
 int /*<<< orphan*/  CONFLICTING_OURS_OID ; 
 int /*<<< orphan*/  CONFLICTING_THEIRS_OID ; 
 TYPE_1__ GIT_CHECKOUT_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_CHECKOUT_UPDATE_ONLY ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rewritefile (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_index (struct checkout_index_entry*,int) ; 
 int /*<<< orphan*/  ensure_workdir (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ensure_workdir_contents (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_index ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_checkout_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_exists (char*) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 

void test_checkout_conflict__update_only(void)
{
	git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;

	struct checkout_index_entry checkout_index_entries[] = {
		{ 0100644, AUTOMERGEABLE_ANCESTOR_OID, 1, "automergeable.txt" },
		{ 0100644, AUTOMERGEABLE_OURS_OID, 2, "automergeable.txt" },
		{ 0100644, AUTOMERGEABLE_THEIRS_OID, 3, "automergeable.txt" },

		{ 0100644, CONFLICTING_ANCESTOR_OID, 1, "modify-delete" },
		{ 0100644, CONFLICTING_THEIRS_OID, 3, "modify-delete" },

		{ 0100644, CONFLICTING_ANCESTOR_OID, 1, "directory_file-one" },
		{ 0100644, CONFLICTING_OURS_OID, 2, "directory_file-one" },
		{ 0100644, CONFLICTING_THEIRS_OID, 0, "directory_file-one/file" },

		{ 0100644, CONFLICTING_ANCESTOR_OID, 1, "directory_file-two" },
		{ 0100644, CONFLICTING_OURS_OID, 0, "directory_file-two/file" },
		{ 0100644, CONFLICTING_THEIRS_OID, 3, "directory_file-two" },
	};

	opts.checkout_strategy |= GIT_CHECKOUT_UPDATE_ONLY;

	create_index(checkout_index_entries, 3);
	cl_git_pass(git_index_write(g_index));

	cl_git_pass(p_mkdir("merge-resolve/directory_file-two", 0777));
	cl_git_rewritefile("merge-resolve/directory_file-two/file", CONFLICTING_OURS_FILE);

	cl_git_pass(git_checkout_index(g_repo, g_index, &opts));

	ensure_workdir_contents("automergeable.txt", AUTOMERGEABLE_MERGED_FILE);
	ensure_workdir("directory_file-two/file", 0100644, CONFLICTING_OURS_OID);

	cl_assert(!git_path_exists("merge-resolve/modify-delete"));
	cl_assert(!git_path_exists("merge-resolve/test-one.txt"));
	cl_assert(!git_path_exists("merge-resolve/test-one-side-one.txt"));
	cl_assert(!git_path_exists("merge-resolve/test-one-side-two.txt"));
	cl_assert(!git_path_exists("merge-resolve/test-one.txt~ours"));
	cl_assert(!git_path_exists("merge-resolve/test-one.txt~theirs"));
	cl_assert(!git_path_exists("merge-resolve/directory_file-one/file"));
	cl_assert(!git_path_exists("merge-resolve/directory_file-one~ours"));
	cl_assert(!git_path_exists("merge-resolve/directory_file-two~theirs"));
}