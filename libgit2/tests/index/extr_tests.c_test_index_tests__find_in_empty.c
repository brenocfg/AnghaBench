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
struct TYPE_3__ {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 scalar_t__ GIT_ENOTFOUND ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 scalar_t__ git_index_find (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_open (int /*<<< orphan*/ **,char*) ; 
 TYPE_1__* test_entries ; 

void test_index_tests__find_in_empty(void)
{
   git_index *index;
   unsigned int i;

   cl_git_pass(git_index_open(&index, "fake-index"));

   for (i = 0; i < ARRAY_SIZE(test_entries); ++i) {
		cl_assert(GIT_ENOTFOUND == git_index_find(NULL, index, test_entries[i].path));
   }

   git_index_free(index);
}