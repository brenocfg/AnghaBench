#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  CONTENT ; 
 int /*<<< orphan*/  add_to_workdir (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_index_find (size_t*,int /*<<< orphan*/ *,char const*) ; 
 TYPE_1__* git_index_get_byindex (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  git_oid_streq (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void assert_proper_normalization(git_index *index, const char *filename, const char *expected_sha)
{
	size_t index_pos;
	const git_index_entry *entry;

	add_to_workdir(filename, CONTENT);
	cl_git_pass(git_index_add_bypath(index, filename));

	cl_assert(!git_index_find(&index_pos, index, filename));

	entry = git_index_get_byindex(index, index_pos);
	cl_assert_equal_i(0, git_oid_streq(&entry->id, expected_sha));
}