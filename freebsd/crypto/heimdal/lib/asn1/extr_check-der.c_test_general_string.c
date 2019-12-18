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
typedef  int /*<<< orphan*/  tests ;
struct test_case {int member_1; char* member_2; char** val; int /*<<< orphan*/ * name; int /*<<< orphan*/ * member_0; } ;
typedef  int /*<<< orphan*/  generic_length ;
typedef  int /*<<< orphan*/  generic_free ;
typedef  int /*<<< orphan*/  generic_encode ;
typedef  int /*<<< orphan*/  generic_decode ;

/* Variables and functions */
 scalar_t__ asprintf (int /*<<< orphan*/ **,char*,char*) ; 
 int /*<<< orphan*/  cmp_general_string ; 
 scalar_t__ der_free_general_string ; 
 scalar_t__ der_get_general_string ; 
 scalar_t__ der_length_general_string ; 
 scalar_t__ der_put_general_string ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int generic_test (struct test_case*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
test_general_string (void)
{
    char *s1 = "Test User 1";

    struct test_case tests[] = {
	{NULL, 11, "\x54\x65\x73\x74\x20\x55\x73\x65\x72\x20\x31"}
    };
    int ret, ntests = sizeof(tests) / sizeof(*tests);

    tests[0].val = &s1;
    if (asprintf (&tests[0].name, "the string \"%s\"", s1) < 0)
	errx(1, "malloc");
    if (tests[0].name == NULL)
	errx(1, "malloc");

    ret = generic_test (tests, ntests, sizeof(unsigned char *),
			(generic_encode)der_put_general_string,
			(generic_length)der_length_general_string,
			(generic_decode)der_get_general_string,
			(generic_free)der_free_general_string,
			cmp_general_string,
			NULL);
    free(tests[0].name);
    return ret;
}