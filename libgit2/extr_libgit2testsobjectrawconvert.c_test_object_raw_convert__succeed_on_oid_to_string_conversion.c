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
typedef  int /*<<< orphan*/  out ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int GIT_OID_HEXSZ ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char const*) ; 
 char* git_oid_tostr (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

void test_object_raw_convert__succeed_on_oid_to_string_conversion(void)
{
	const char *exp = "16a0123456789abcdef4b775213c23a8bd74f5e0";
	git_oid in;
	char out[GIT_OID_HEXSZ + 1];
	char *str;
	int i;

	cl_git_pass(git_oid_fromstr(&in, exp));

	/* NULL buffer pointer, returns static empty string */
	str = git_oid_tostr(NULL, sizeof(out), &in);
	cl_assert(str && *str == '\0' && str != out);

	/* zero buffer size, returns static empty string */
	str = git_oid_tostr(out, 0, &in);
	cl_assert(str && *str == '\0' && str != out);

	/* NULL oid pointer, sets existing buffer to empty string */
	str = git_oid_tostr(out, sizeof(out), NULL);
	cl_assert(str && *str == '\0' && str == out);

	/* n == 1, returns out as an empty string */
	str = git_oid_tostr(out, 1, &in);
	cl_assert(str && *str == '\0' && str == out);

	for (i = 1; i < GIT_OID_HEXSZ; i++) {
		out[i+1] = 'Z';
		str = git_oid_tostr(out, i+1, &in);
		/* returns out containing c-string */
		cl_assert(str && str == out);
		/* must be '\0' terminated */
		cl_assert(*(str+i) == '\0');
		/* must not touch bytes past end of string */
		cl_assert(*(str+(i+1)) == 'Z');
		/* i == n-1 charaters of string */
		cl_git_pass(strncmp(exp, out, i));
	}

	/* returns out as hex formatted c-string */
	str = git_oid_tostr(out, sizeof(out), &in);
	cl_assert(str && str == out && *(str+GIT_OID_HEXSZ) == '\0');
	cl_assert_equal_s(exp, out);
}