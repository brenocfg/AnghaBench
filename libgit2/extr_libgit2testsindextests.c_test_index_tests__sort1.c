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
struct TYPE_4__ {int /*<<< orphan*/  entries; } ;
typedef  TYPE_1__ git_index ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_index_open (TYPE_1__**,char*) ; 
 int /*<<< orphan*/  git_vector_is_sorted (int /*<<< orphan*/ *) ; 

void test_index_tests__sort1(void)
{
   /* sort the entires in an empty index */
   git_index *index;

   cl_git_pass(git_index_open(&index, "fake-index"));

   /* FIXME: this test is slightly dumb */
   cl_assert(git_vector_is_sorted(&index->entries));

   git_index_free(index);
}