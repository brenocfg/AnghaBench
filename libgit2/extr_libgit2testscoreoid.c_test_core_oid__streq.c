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
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_streq (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  id ; 
 int /*<<< orphan*/  idp ; 
 char* str_oid ; 

void test_core_oid__streq(void)
{
	cl_assert_equal_i(0, git_oid_streq(&id, str_oid));
	cl_assert_equal_i(-1, git_oid_streq(&id, "deadbeefdeadbeefdeadbeefdeadbeefdeadbeef"));

	cl_assert_equal_i(-1, git_oid_streq(&id, "deadbeef"));
	cl_assert_equal_i(-1, git_oid_streq(&id, "I'm not an oid.... :)"));

	cl_assert_equal_i(0, git_oid_streq(&idp, "ae90f12eea699729ed0000000000000000000000"));
	cl_assert_equal_i(0, git_oid_streq(&idp, "ae90f12eea699729ed"));
	cl_assert_equal_i(-1, git_oid_streq(&idp, "ae90f12eea699729ed1"));
	cl_assert_equal_i(-1, git_oid_streq(&idp, "ae90f12eea699729ec"));
	cl_assert_equal_i(-1, git_oid_streq(&idp, "deadbeefdeadbeefdeadbeefdeadbeefdeadbeef"));

	cl_assert_equal_i(-1, git_oid_streq(&idp, "deadbeef"));
	cl_assert_equal_i(-1, git_oid_streq(&idp, "I'm not an oid.... :)"));
}