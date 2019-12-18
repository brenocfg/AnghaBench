#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 size_t ARRAY_SIZE (char const**) ; 
 int /*<<< orphan*/  GIT_INDEX_STAGE_NORMAL ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_sz (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_index_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_index_get_bypath (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

void test_index_version__can_read_v4(void)
{
	const char *paths[] = {
	    "file.tx", "file.txt", "file.txz", "foo", "zzz",
	};
	git_index *index;
	size_t i;

	g_repo = cl_git_sandbox_init("indexv4");

	cl_git_pass(git_repository_index(&index, g_repo));
	cl_assert_equal_sz(git_index_entrycount(index), 5);

	for (i = 0; i < ARRAY_SIZE(paths); i++) {
		const git_index_entry *entry =
		    git_index_get_bypath(index, paths[i], GIT_INDEX_STAGE_NORMAL);

		cl_assert(entry != NULL);
	}

	git_index_free(index);
}