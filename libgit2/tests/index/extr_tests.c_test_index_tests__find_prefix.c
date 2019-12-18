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
struct TYPE_3__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 scalar_t__ GIT_ENOTFOUND ; 
 int /*<<< orphan*/  TEST_INDEX_PATH ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (scalar_t__) ; 
 scalar_t__ git__strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ git_index_find_prefix (size_t*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 TYPE_1__* git_index_get_byindex (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ git_index_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

void test_index_tests__find_prefix(void)
{
   git_index *index;
   const git_index_entry *entry;
   size_t pos;

   cl_git_pass(git_index_open(&index, TEST_INDEX_PATH));

   cl_git_pass(git_index_find_prefix(&pos, index, "src"));
   entry = git_index_get_byindex(index, pos);
   cl_assert(git__strcmp(entry->path, "src/block-sha1/sha1.c") == 0);

   cl_git_pass(git_index_find_prefix(&pos, index, "src/co"));
   entry = git_index_get_byindex(index, pos);
   cl_assert(git__strcmp(entry->path, "src/commit.c") == 0);

   cl_assert(GIT_ENOTFOUND == git_index_find_prefix(NULL, index, "blah"));

   git_index_free(index);
}