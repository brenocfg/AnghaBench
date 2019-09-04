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
struct checkout_index_entry {int member_0; int member_2; char* member_3; int /*<<< orphan*/  member_1; } ;
typedef  int /*<<< orphan*/  git_checkout_options ;

/* Variables and functions */
 int /*<<< orphan*/  AUTOMERGEABLE_ANCESTOR_OID ; 
 int /*<<< orphan*/  AUTOMERGEABLE_MERGED_FILE ; 
 int /*<<< orphan*/  AUTOMERGEABLE_OURS_OID ; 
 int /*<<< orphan*/  AUTOMERGEABLE_THEIRS_OID ; 
 int /*<<< orphan*/  GIT_CHECKOUT_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_index (struct checkout_index_entry*,int) ; 
 int /*<<< orphan*/  ensure_workdir_contents (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_index ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_checkout_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ ) ; 

void test_checkout_conflict__automerge(void)
{
	git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;

	struct checkout_index_entry checkout_index_entries[] = {
		{ 0100644, AUTOMERGEABLE_ANCESTOR_OID, 1, "automergeable.txt" },
		{ 0100644, AUTOMERGEABLE_OURS_OID, 2, "automergeable.txt" },
		{ 0100644, AUTOMERGEABLE_THEIRS_OID, 3, "automergeable.txt" },
	};

	create_index(checkout_index_entries, 3);
	cl_git_pass(git_index_write(g_index));

	cl_git_pass(git_checkout_index(g_repo, g_index, &opts));

	ensure_workdir_contents("automergeable.txt", AUTOMERGEABLE_MERGED_FILE);
}