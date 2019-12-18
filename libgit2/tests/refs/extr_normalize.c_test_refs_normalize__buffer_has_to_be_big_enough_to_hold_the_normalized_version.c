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
 int /*<<< orphan*/  GIT_REFERENCE_FORMAT_NORMAL ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_normalize_name (char*,int,char*,int /*<<< orphan*/ ) ; 

void test_refs_normalize__buffer_has_to_be_big_enough_to_hold_the_normalized_version(void)
{
	char buffer_out[21];

	cl_git_pass(git_reference_normalize_name(
		buffer_out, 21, "refs//heads///long///name", GIT_REFERENCE_FORMAT_NORMAL));
	cl_git_fail(git_reference_normalize_name(
		buffer_out, 20, "refs//heads///long///name", GIT_REFERENCE_FORMAT_NORMAL));
}