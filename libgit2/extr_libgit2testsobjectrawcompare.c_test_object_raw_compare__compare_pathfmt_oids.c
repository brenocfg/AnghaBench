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
 int GIT_OID_HEXSZ ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_oid_pathfmt (char*,int /*<<< orphan*/ *) ; 

void test_object_raw_compare__compare_pathfmt_oids(void)
{
	const char *exp1 = "16a0123456789abcdef4b775213c23a8bd74f5e0";
	const char *exp2 = "16/a0123456789abcdef4b775213c23a8bd74f5e0";
	git_oid in;
	char out[GIT_OID_HEXSZ + 2];

	cl_git_pass(git_oid_fromstr(&in, exp1));

	/* Format doesn't touch the last byte */
	out[GIT_OID_HEXSZ + 1] = 'Z';
	git_oid_pathfmt(out, &in);
	cl_assert(out[GIT_OID_HEXSZ + 1] == 'Z');

	/* Format produced the right result */
	out[GIT_OID_HEXSZ + 1] = '\0';
	cl_assert_equal_s(exp2, out);
}