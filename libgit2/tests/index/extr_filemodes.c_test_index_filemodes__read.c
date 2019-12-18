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
struct TYPE_3__ {int mode; } ;
typedef  TYPE_1__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 scalar_t__ git_index_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 TYPE_1__* git_index_get_byindex (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

void test_index_filemodes__read(void)
{
	git_index *index;
	unsigned int i;
	static bool expected[6] = { 0, 1, 0, 1, 0, 1 };

	cl_git_pass(git_repository_index(&index, g_repo));
	cl_assert_equal_i(6, (int)git_index_entrycount(index));

	for (i = 0; i < 6; ++i) {
		const git_index_entry *entry = git_index_get_byindex(index, i);
		cl_assert(entry != NULL);
		cl_assert(((entry->mode & 0100) ? 1 : 0) == expected[i]);
	}

	git_index_free(index);
}