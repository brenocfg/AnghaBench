#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  snap; } ;
typedef  TYPE_2__ git_index_iterator ;
struct TYPE_10__ {size_t seconds; } ;
struct TYPE_12__ {size_t file_size; TYPE_1__ mtime; int /*<<< orphan*/  path; } ;
typedef  TYPE_3__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;
struct TYPE_13__ {size_t mtime; size_t file_size; int /*<<< orphan*/  path; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_4__*) ; 
 int GIT_ITEROVER ; 
 int /*<<< orphan*/  TEST_INDEX_PATH ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_i (size_t,size_t) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_fail (char*) ; 
 int /*<<< orphan*/  cl_git_fail (int) ; 
 int /*<<< orphan*/  cl_git_pass (int) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_iterator_free (TYPE_2__*) ; 
 int git_index_iterator_new (TYPE_2__**,int /*<<< orphan*/ *) ; 
 int git_index_iterator_next (TYPE_3__ const**,TYPE_2__*) ; 
 int git_index_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_vector_is_sorted (int /*<<< orphan*/ *) ; 
 TYPE_4__* test_entries ; 

void test_index_tests__can_iterate(void)
{
	git_index *index;
	git_index_iterator *iterator;
	const git_index_entry *entry;
	size_t i, iterator_idx = 0, found = 0;
	int ret;

	cl_git_pass(git_index_open(&index, TEST_INDEX_PATH));
	cl_git_pass(git_index_iterator_new(&iterator, index));

	cl_assert(git_vector_is_sorted(&iterator->snap));

	for (i = 0; i < ARRAY_SIZE(test_entries); i++) {
		/* Advance iterator to next test entry index */
		do {
			ret = git_index_iterator_next(&entry, iterator);

			if (ret == GIT_ITEROVER)
				cl_fail("iterator did not contain all test entries");

			cl_git_pass(ret);
		} while (iterator_idx++ < test_entries[i].index);

		cl_assert_equal_s(entry->path, test_entries[i].path);
		cl_assert_equal_i(entry->mtime.seconds, test_entries[i].mtime);
		cl_assert_equal_i(entry->file_size, test_entries[i].file_size);
		found++;
	}

	while ((ret = git_index_iterator_next(&entry, iterator)) == 0)
		;

	if (ret != GIT_ITEROVER)
		cl_git_fail(ret);

	cl_assert_equal_i(found, ARRAY_SIZE(test_entries));

	git_index_iterator_free(iterator);
	git_index_free(index);
}