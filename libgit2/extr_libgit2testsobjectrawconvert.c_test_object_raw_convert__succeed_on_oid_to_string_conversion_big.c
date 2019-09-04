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
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char const*) ; 
 char* git_oid_tostr (char*,int,int /*<<< orphan*/ *) ; 

void test_object_raw_convert__succeed_on_oid_to_string_conversion_big(void)
{
	const char *exp = "16a0123456789abcdef4b775213c23a8bd74f5e0";
	git_oid in;
	char big[GIT_OID_HEXSZ + 1 + 3]; /* note + 4 => big buffer */
	char *str;

	cl_git_pass(git_oid_fromstr(&in, exp));

	/* place some tail material */
	big[GIT_OID_HEXSZ+0] = 'W'; /* should be '\0' afterwards */
	big[GIT_OID_HEXSZ+1] = 'X'; /* should remain untouched   */
	big[GIT_OID_HEXSZ+2] = 'Y'; /* ditto */
	big[GIT_OID_HEXSZ+3] = 'Z'; /* ditto */

	/* returns big as hex formatted c-string */
	str = git_oid_tostr(big, sizeof(big), &in);
	cl_assert(str && str == big && *(str+GIT_OID_HEXSZ) == '\0');
	cl_assert_equal_s(exp, big);

	/* check tail material is untouched */
	cl_assert(str && str == big && *(str+GIT_OID_HEXSZ+1) == 'X');
	cl_assert(str && str == big && *(str+GIT_OID_HEXSZ+2) == 'Y');
	cl_assert(str && str == big && *(str+GIT_OID_HEXSZ+3) == 'Z');
}