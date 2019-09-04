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
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstrp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  id ; 
 int /*<<< orphan*/  idm ; 
 int /*<<< orphan*/  idp ; 
 int /*<<< orphan*/  str_oid ; 
 int /*<<< orphan*/  str_oid_m ; 
 int /*<<< orphan*/  str_oid_p ; 

void test_core_oid__initialize(void)
{
	cl_git_pass(git_oid_fromstr(&id, str_oid));
	cl_git_pass(git_oid_fromstrp(&idp, str_oid_p));
	cl_git_fail(git_oid_fromstrp(&idm, str_oid_m));
}