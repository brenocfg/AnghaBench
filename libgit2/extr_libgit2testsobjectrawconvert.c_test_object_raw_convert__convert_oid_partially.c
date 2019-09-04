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
typedef  int /*<<< orphan*/  big ;

/* Variables and functions */
 int GIT_OID_HEXSZ ; 
 int /*<<< orphan*/  check_partial_oid (char*,int,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_oid_nfmt (char*,int,int /*<<< orphan*/ *) ; 

void test_object_raw_convert__convert_oid_partially(void)
{
	const char *exp = "16a0123456789abcdef4b775213c23a8bd74f5e0";
	git_oid in;
	char big[GIT_OID_HEXSZ + 1 + 3]; /* note + 4 => big buffer */

	cl_git_pass(git_oid_fromstr(&in, exp));

	git_oid_nfmt(big, sizeof(big), &in);
	cl_assert_equal_s(exp, big);

	git_oid_nfmt(big, GIT_OID_HEXSZ + 1, &in);
	cl_assert_equal_s(exp, big);

	check_partial_oid(big, 1, &in, "1");
	check_partial_oid(big, 2, &in, "16");
	check_partial_oid(big, 3, &in, "16a");
	check_partial_oid(big, 4, &in, "16a0");
	check_partial_oid(big, 5, &in, "16a01");

	check_partial_oid(big, GIT_OID_HEXSZ, &in, exp);
	check_partial_oid(
		big, GIT_OID_HEXSZ - 1, &in, "16a0123456789abcdef4b775213c23a8bd74f5e");
	check_partial_oid(
		big, GIT_OID_HEXSZ - 2, &in, "16a0123456789abcdef4b775213c23a8bd74f5");
	check_partial_oid(
		big, GIT_OID_HEXSZ - 3, &in, "16a0123456789abcdef4b775213c23a8bd74f");
}