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
 int /*<<< orphan*/  GIT_EEXISTS ; 
 int /*<<< orphan*/  assert_submodule_exists (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  refute_submodule_exists (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void baseline_tests(void)
{
	/* small baseline that should work even if we change the index or make
	 * commits from the index
	 */
	assert_submodule_exists(g_repo, "sm_unchanged");
	assert_submodule_exists(g_repo, "sm_gitmodules_only");
	refute_submodule_exists(g_repo, "not-submodule", GIT_EEXISTS);
}