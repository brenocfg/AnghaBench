#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int on_disk; int /*<<< orphan*/ * tree; int /*<<< orphan*/  entries; } ;
typedef  TYPE_1__ git_index ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_INDEX2_PATH ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 scalar_t__ git_index_entrycount (TYPE_1__*) ; 
 int /*<<< orphan*/  git_index_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_index_open (TYPE_1__**,int /*<<< orphan*/ ) ; 
 int git_vector_is_sorted (int /*<<< orphan*/ *) ; 
 scalar_t__ index_entry_count_2 ; 

void test_index_tests__gitgit_index(void)
{
   git_index *index;

   cl_git_pass(git_index_open(&index, TEST_INDEX2_PATH));
   cl_assert(index->on_disk);

   cl_assert(git_index_entrycount(index) == index_entry_count_2);
   cl_assert(git_vector_is_sorted(&index->entries));
   cl_assert(index->tree != NULL);

   git_index_free(index);
}