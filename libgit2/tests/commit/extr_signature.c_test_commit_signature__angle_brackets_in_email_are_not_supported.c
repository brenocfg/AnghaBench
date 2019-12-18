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
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_build_signature (char*,char*,int,int) ; 

void test_commit_signature__angle_brackets_in_email_are_not_supported(void)
{
	cl_git_fail(try_build_signature("Phil Haack", ">phil@haack", 1234567890, 60));
	cl_git_fail(try_build_signature("Phil Haack", "phil@>haack", 1234567890, 60));
	cl_git_fail(try_build_signature("Phil Haack", "<phil@haack>", 1234567890, 60));
}