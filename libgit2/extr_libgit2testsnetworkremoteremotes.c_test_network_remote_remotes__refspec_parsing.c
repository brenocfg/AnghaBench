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
 int /*<<< orphan*/  _refspec ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_refspec_dst (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_refspec_src (int /*<<< orphan*/ ) ; 

void test_network_remote_remotes__refspec_parsing(void)
{
	cl_assert_equal_s(git_refspec_src(_refspec), "refs/heads/*");
	cl_assert_equal_s(git_refspec_dst(_refspec), "refs/remotes/test/*");
}