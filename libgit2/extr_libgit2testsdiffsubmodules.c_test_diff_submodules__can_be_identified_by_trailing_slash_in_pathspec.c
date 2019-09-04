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

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char const**) ; 
 int /*<<< orphan*/  ensure_submodules_found (int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  setup_fixture_submod2 () ; 

void test_diff_submodules__can_be_identified_by_trailing_slash_in_pathspec(void)
{
	const char *one_path_without_slash[] = { "sm_changed_head" };
	const char *one_path_with_slash[] = { "sm_changed_head/" };
	const char *many_paths_without_slashes[] = { "sm_changed_head", "sm_changed_index" };
	const char *many_paths_with_slashes[] = { "sm_changed_head/", "sm_changed_index/" };

	g_repo = setup_fixture_submod2();

	ensure_submodules_found(g_repo, one_path_without_slash, ARRAY_SIZE(one_path_without_slash));
	ensure_submodules_found(g_repo, one_path_with_slash, ARRAY_SIZE(one_path_with_slash));
	ensure_submodules_found(g_repo, many_paths_without_slashes, ARRAY_SIZE(many_paths_without_slashes));
	ensure_submodules_found(g_repo, many_paths_with_slashes, ARRAY_SIZE(many_paths_with_slashes));
}