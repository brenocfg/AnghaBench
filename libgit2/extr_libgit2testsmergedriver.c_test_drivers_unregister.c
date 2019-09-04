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
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_merge_driver_unregister (char*) ; 

__attribute__((used)) static void test_drivers_unregister(void)
{
	cl_git_pass(git_merge_driver_unregister("custom"));
	cl_git_pass(git_merge_driver_unregister("*"));
}