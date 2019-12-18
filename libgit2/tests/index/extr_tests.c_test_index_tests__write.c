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
struct TYPE_5__ {int /*<<< orphan*/  on_disk; } ;
typedef  TYPE_1__ git_index ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_INDEXBIG_PATH ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_file (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  files_are_equal (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_index_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_index_open (TYPE_1__**,char*) ; 
 int /*<<< orphan*/  git_index_write (TYPE_1__*) ; 
 int /*<<< orphan*/  p_unlink (char*) ; 

void test_index_tests__write(void)
{
   git_index *index;

   copy_file(TEST_INDEXBIG_PATH, "index_rewrite");

   cl_git_pass(git_index_open(&index, "index_rewrite"));
   cl_assert(index->on_disk);

   cl_git_pass(git_index_write(index));
   files_are_equal(TEST_INDEXBIG_PATH, "index_rewrite");

   git_index_free(index);

   p_unlink("index_rewrite");
}