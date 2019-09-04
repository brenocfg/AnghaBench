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
 int /*<<< orphan*/ * g_reflog ; 
 int /*<<< orphan*/  git_reflog_free (int /*<<< orphan*/ *) ; 

void test_refs_reflog_drop__cleanup(void)
{
	git_reflog_free(g_reflog);
	g_reflog = NULL;

	cl_git_sandbox_cleanup();
}