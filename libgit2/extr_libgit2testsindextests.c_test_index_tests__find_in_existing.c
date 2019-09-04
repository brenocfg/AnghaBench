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
typedef  int /*<<< orphan*/  git_index ;
struct TYPE_3__ {size_t index; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  TEST_INDEX_PATH ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_find (size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 TYPE_1__* test_entries ; 

void test_index_tests__find_in_existing(void)
{
   git_index *index;
   unsigned int i;

   cl_git_pass(git_index_open(&index, TEST_INDEX_PATH));

   for (i = 0; i < ARRAY_SIZE(test_entries); ++i) {
		size_t idx;

		cl_assert(!git_index_find(&idx, index, test_entries[i].path));
		cl_assert(idx == test_entries[i].index);
   }

   git_index_free(index);
}