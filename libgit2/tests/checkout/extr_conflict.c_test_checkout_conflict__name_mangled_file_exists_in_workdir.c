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
struct checkout_name_entry {char* member_0; char* member_1; char* member_2; } ;
struct checkout_index_entry {int member_0; char* member_1; int member_2; char* member_3; } ;
struct TYPE_4__ {int /*<<< orphan*/  checkout_strategy; } ;
typedef  TYPE_1__ git_checkout_options ;

/* Variables and functions */
 char* CONFLICTING_ANCESTOR_OID ; 
 char* CONFLICTING_OURS_OID ; 
 char* CONFLICTING_THEIRS_OID ; 
 TYPE_1__ GIT_CHECKOUT_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_CHECKOUT_SAFE ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rewritefile (char*,char*) ; 
 int /*<<< orphan*/  create_index (struct checkout_index_entry*,int) ; 
 int /*<<< orphan*/  create_index_names (struct checkout_name_entry*,int) ; 
 int /*<<< orphan*/  ensure_workdir (char*,int,char*) ; 
 int /*<<< orphan*/  g_index ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_checkout_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ ) ; 

void test_checkout_conflict__name_mangled_file_exists_in_workdir(void)
{
	git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;

	struct checkout_index_entry checkout_index_entries[] = {
		{ 0100644, "b42712cfe99a1a500b2a51fe984e0b8a7702ba11", 1, "test-one-side-one.txt" },
		{ 0100644, "b42712cfe99a1a500b2a51fe984e0b8a7702ba11", 3, "test-one-side-one.txt" },
		{ 0100644, "b69fe837e4cecfd4c9a40cdca7c138468687df07", 1, "test-one-side-two.txt" },
		{ 0100644, "b69fe837e4cecfd4c9a40cdca7c138468687df07", 2, "test-one-side-two.txt" },
		{ 0100644, "b42712cfe99a1a500b2a51fe984e0b8a7702ba11", 2, "test-one.txt" },
		{ 0100644, "b69fe837e4cecfd4c9a40cdca7c138468687df07", 3, "test-one.txt" },

		{ 0100644, "b42712cfe99a1a500b2a51fe984e0b8a7702ba11", 1, "test-two-side-one.txt" },
		{ 0100644, "b42712cfe99a1a500b2a51fe984e0b8a7702ba11", 3, "test-two-side-one.txt" },
		{ 0100644, "b69fe837e4cecfd4c9a40cdca7c138468687df07", 1, "test-two-side-two.txt" },
		{ 0100644, "b69fe837e4cecfd4c9a40cdca7c138468687df07", 2, "test-two-side-two.txt" },
		{ 0100644, "b42712cfe99a1a500b2a51fe984e0b8a7702ba11", 2, "test-two.txt" },
		{ 0100644, "b69fe837e4cecfd4c9a40cdca7c138468687df07", 3, "test-two.txt" },

		{ 0100644, "b42712cfe99a1a500b2a51fe984e0b8a7702ba11", 1, "test-three-side-one.txt" },
		{ 0100644, "b42712cfe99a1a500b2a51fe984e0b8a7702ba11", 3, "test-three-side-one.txt" },
		{ 0100644, "b69fe837e4cecfd4c9a40cdca7c138468687df07", 1, "test-three-side-two.txt" },
		{ 0100644, "b69fe837e4cecfd4c9a40cdca7c138468687df07", 2, "test-three-side-two.txt" },
		{ 0100644, "b42712cfe99a1a500b2a51fe984e0b8a7702ba11", 2, "test-three.txt" },
		{ 0100644, "b69fe837e4cecfd4c9a40cdca7c138468687df07", 3, "test-three.txt" },

		{ 0100644, CONFLICTING_ANCESTOR_OID, 1, "directory_file-one" },
		{ 0100644, CONFLICTING_OURS_OID, 2, "directory_file-one" },
		{ 0100644, CONFLICTING_THEIRS_OID, 0, "directory_file-one/file" },

		{ 0100644, CONFLICTING_ANCESTOR_OID, 1, "directory_file-two" },
		{ 0100644, CONFLICTING_OURS_OID, 0, "directory_file-two/file" },
		{ 0100644, CONFLICTING_THEIRS_OID, 3, "directory_file-two" },
	};

	struct checkout_name_entry checkout_name_entries[] = {
		{
			"test-one-side-one.txt",
			"test-one.txt",
			"test-one-side-one.txt"
		},
		{
			"test-one-side-two.txt",
			"test-one-side-two.txt",
			"test-one.txt"
		},

		{
			"test-two-side-one.txt",
			"test-two.txt",
			"test-two-side-one.txt"
		},
		{
			"test-two-side-two.txt",
			"test-two-side-two.txt",
			"test-two.txt"
		},

		{
			"test-three-side-one.txt",
			"test-three.txt",
			"test-three-side-one.txt"
		},
		{
			"test-three-side-two.txt",
			"test-three-side-two.txt",
			"test-three.txt"
		}
	};

	opts.checkout_strategy |= GIT_CHECKOUT_SAFE;

	create_index(checkout_index_entries, 24);
	create_index_names(checkout_name_entries, 6);
	cl_git_pass(git_index_write(g_index));

	/* Add some files on disk that conflict with the names that would be chosen
	 * for the files written for each side. */

	cl_git_rewritefile("merge-resolve/test-one.txt~ours",
		"Expect index contents to be written to ~ours_0");
	cl_git_rewritefile("merge-resolve/test-one.txt~theirs",
		"Expect index contents to be written to ~theirs_0");

	cl_git_rewritefile("merge-resolve/test-two.txt~ours",
		"Expect index contents to be written to ~ours_3");
	cl_git_rewritefile("merge-resolve/test-two.txt~theirs",
		"Expect index contents to be written to ~theirs_3");
	cl_git_rewritefile("merge-resolve/test-two.txt~ours_0",
		"Expect index contents to be written to ~ours_3");
	cl_git_rewritefile("merge-resolve/test-two.txt~theirs_0",
		"Expect index contents to be written to ~theirs_3");
	cl_git_rewritefile("merge-resolve/test-two.txt~ours_1",
		"Expect index contents to be written to ~ours_3");
	cl_git_rewritefile("merge-resolve/test-two.txt~theirs_1",
		"Expect index contents to be written to ~theirs_3");
	cl_git_rewritefile("merge-resolve/test-two.txt~ours_2",
		"Expect index contents to be written to ~ours_3");
	cl_git_rewritefile("merge-resolve/test-two.txt~theirs_2",
		"Expect index contents to be written to ~theirs_3");

	cl_git_rewritefile("merge-resolve/test-three.txt~Ours",
		"Expect case insensitive filesystems to create ~ours_0");
	cl_git_rewritefile("merge-resolve/test-three.txt~THEIRS",
		"Expect case insensitive filesystems to create ~theirs_0");

	cl_git_rewritefile("merge-resolve/directory_file-one~ours",
		"Index contents written to ~ours_0 in this D/F conflict");
	cl_git_rewritefile("merge-resolve/directory_file-two~theirs",
		"Index contents written to ~theirs_0 in this D/F conflict");

	cl_git_pass(git_checkout_index(g_repo, g_index, &opts));

	ensure_workdir("test-one.txt~ours_0",
		0100644, "b42712cfe99a1a500b2a51fe984e0b8a7702ba11");
	ensure_workdir("test-one.txt~theirs_0",
		0100644, "b69fe837e4cecfd4c9a40cdca7c138468687df07");

	ensure_workdir("test-two.txt~ours_3",
		0100644, "b42712cfe99a1a500b2a51fe984e0b8a7702ba11");
	ensure_workdir("test-two.txt~theirs_3",
		0100644, "b69fe837e4cecfd4c9a40cdca7c138468687df07");

	/* Name is mangled on case insensitive only */
#if defined(GIT_WIN32) || defined(__APPLE__)
	ensure_workdir("test-three.txt~ours_0",
		0100644, "b42712cfe99a1a500b2a51fe984e0b8a7702ba11");
	ensure_workdir("test-three.txt~theirs_0",
		0100644, "b69fe837e4cecfd4c9a40cdca7c138468687df07");
#else
	ensure_workdir("test-three.txt~ours",
		0100644, "b42712cfe99a1a500b2a51fe984e0b8a7702ba11");
	ensure_workdir("test-three.txt~theirs",
		0100644, "b69fe837e4cecfd4c9a40cdca7c138468687df07");
#endif

	ensure_workdir("directory_file-one~ours_0", 0100644, CONFLICTING_OURS_OID);
	ensure_workdir("directory_file-two~theirs_0", 0100644, CONFLICTING_THEIRS_OID);
}