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
struct TYPE_4__ {int /*<<< orphan*/  file_size; } ;
typedef  TYPE_1__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (TYPE_1__ const*) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 TYPE_1__* git_index_get_bypath (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_race () ; 

void test_index_racy__smudges_index_entry_on_save(void)
{
	git_index *index;
	const git_index_entry *entry;

	setup_race();

	/* write the index, which will smudge anything that had the same timestamp
	 * as the index when the index was loaded.  that way future loads of the
	 * index (with the new timestamp) will know that these files were not
	 * clean.
	 */

	cl_git_pass(git_repository_index__weakptr(&index, g_repo));
	cl_git_pass(git_index_write(index));

	cl_assert(entry = git_index_get_bypath(index, "A", 0));
	cl_assert_equal_i(0, entry->file_size);
}