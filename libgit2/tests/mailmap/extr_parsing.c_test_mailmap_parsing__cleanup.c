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
 int /*<<< orphan*/  cl_git_sandbox_cleanup () ; 
 int /*<<< orphan*/  g_config ; 
 int /*<<< orphan*/  g_mailmap ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_mailmap_free (int /*<<< orphan*/ ) ; 

void test_mailmap_parsing__cleanup(void)
{
	git_mailmap_free(g_mailmap);
	git_config_free(g_config);
	cl_git_sandbox_cleanup();
}