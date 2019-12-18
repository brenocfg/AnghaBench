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
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  GITATTR ; 
 int /*<<< orphan*/  add_to_workdir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_proper_normalization (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

void test_attr_repo__staging_properly_normalizes_line_endings_according_to_gitattributes_directives(void)
{
	git_index* index;

	cl_git_pass(git_repository_index(&index, g_repo));

	add_to_workdir(".gitattributes", GITATTR);

	assert_proper_normalization(index, "text.txt", "22c74203bace3c2e950278c7ab08da0fca9f4e9b");
	assert_proper_normalization(index, "huh.dunno", "22c74203bace3c2e950278c7ab08da0fca9f4e9b");
	assert_proper_normalization(index, "binary.data", "66eeff1fcbacf589e6d70aa70edd3fce5be2b37c");

	git_index_free(index);
}