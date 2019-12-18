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
 int /*<<< orphan*/  TEST_MAILMAP ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_mailmap_from_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mailmap ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

void test_mailmap_basic__initialize(void)
{
	cl_git_pass(git_mailmap_from_buffer(
		&mailmap, TEST_MAILMAP, strlen(TEST_MAILMAP)));
}