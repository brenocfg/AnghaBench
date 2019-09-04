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

/* Variables and functions */
 int /*<<< orphan*/  CONFLICTING_ANCESTOR_OID ; 
 int /*<<< orphan*/  CONFLICTING_OURS_OID ; 
 int /*<<< orphan*/  CONFLICTING_THEIRS_OID ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_index (struct checkout_index_entry*,int) ; 
 int /*<<< orphan*/  g_index ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void create_conflicting_index(void)
{
	struct checkout_index_entry checkout_index_entries[] = {
		{ 0100644, CONFLICTING_ANCESTOR_OID, 1, "conflicting.txt" },
		{ 0100644, CONFLICTING_OURS_OID, 2, "conflicting.txt" },
		{ 0100644, CONFLICTING_THEIRS_OID, 3, "conflicting.txt" },
	};

	create_index(checkout_index_entries, 3);
	cl_git_pass(git_index_write(g_index));
}