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
typedef  int /*<<< orphan*/  git_signature ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_signature_new (int /*<<< orphan*/ **,char*,char*,int,int) ; 

void test_commit_signature__create_zero_char(void)
{
	/* creating a zero character signature */
	git_signature *sign;
	cl_git_fail(git_signature_new(&sign, "", "x@y.z", 1234567890, 60));
	cl_assert(sign == NULL);
}