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
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 

void test_object_raw_fromstr__fail_on_invalid_oid_string(void)
{
	git_oid out;
	cl_git_fail(git_oid_fromstr(&out, ""));
	cl_git_fail(git_oid_fromstr(&out, "moo"));
	cl_git_fail(git_oid_fromstr(&out, "16a67770b7d8d72317c4b775213c23a8bd74f5ez"));
}