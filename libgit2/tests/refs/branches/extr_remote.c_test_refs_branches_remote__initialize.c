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
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  expected_remote_name ; 
 int expected_remote_name_length ; 
 int /*<<< orphan*/  g_repo ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

void test_refs_branches_remote__initialize(void)
{
	g_repo = cl_git_sandbox_init("testrepo");

	expected_remote_name_length = (int)strlen(expected_remote_name) + 1;
}