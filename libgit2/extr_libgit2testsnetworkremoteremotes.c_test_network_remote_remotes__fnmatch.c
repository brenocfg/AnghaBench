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
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_refspec_src_matches (int /*<<< orphan*/ ,char*) ; 

void test_network_remote_remotes__fnmatch(void)
{
	cl_assert(git_refspec_src_matches(_refspec, "refs/heads/master"));
	cl_assert(git_refspec_src_matches(_refspec, "refs/heads/multi/level/branch"));
}