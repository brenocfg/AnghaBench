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
 int /*<<< orphan*/  g_bufferblame ; 
 int /*<<< orphan*/  g_fileblame ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_blame_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ ) ; 

void test_blame_buffer__cleanup(void)
{
	git_blame_free(g_fileblame);
	git_blame_free(g_bufferblame);
	git_repository_free(g_repo);
}