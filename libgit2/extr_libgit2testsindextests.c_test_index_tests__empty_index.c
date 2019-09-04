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
struct TYPE_5__ {scalar_t__ on_disk; int /*<<< orphan*/  entries; } ;
typedef  TYPE_1__ git_index ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 scalar_t__ git_index_entrycount (TYPE_1__*) ; 
 int /*<<< orphan*/  git_index_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_index_open (TYPE_1__**,char*) ; 
 int git_vector_is_sorted (int /*<<< orphan*/ *) ; 

void test_index_tests__empty_index(void)
{
   git_index *index;

   cl_git_pass(git_index_open(&index, "in-memory-index"));
   cl_assert(index->on_disk == 0);

   cl_assert(git_index_entrycount(index) == 0);
   cl_assert(git_vector_is_sorted(&index->entries));

   git_index_free(index);
}