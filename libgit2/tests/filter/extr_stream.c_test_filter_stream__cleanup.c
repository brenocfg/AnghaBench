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
 int /*<<< orphan*/  compress_filter ; 
 int /*<<< orphan*/ * g_repo ; 
 int /*<<< orphan*/  git__free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_filter_unregister (char*) ; 

void test_filter_stream__cleanup(void)
{
	cl_git_sandbox_cleanup();
	g_repo = NULL;

	git_filter_unregister("compress");
	git__free(compress_filter);
}