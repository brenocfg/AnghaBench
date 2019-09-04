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
typedef  int /*<<< orphan*/  git_submodule ;

/* Variables and functions */
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_submodule_add_to_index (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_submodule_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void add_submodule_to_index(const char *name)
{
	git_submodule *sm;
	cl_git_pass(git_submodule_lookup(&sm, g_repo, name));
	cl_git_pass(git_submodule_add_to_index(sm, true));
	git_submodule_free(sm);
}