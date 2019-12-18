#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tests ;
struct test_case {int member_1; char* member_2; int /*<<< orphan*/ * name; TYPE_1__* val; int /*<<< orphan*/ * member_0; } ;
struct TYPE_2__ {int member_0; int /*<<< orphan*/  member_1; } ;
typedef  TYPE_1__ heim_universal_string ;
typedef  int /*<<< orphan*/  generic_length ;
typedef  int /*<<< orphan*/  generic_free ;
typedef  int /*<<< orphan*/  generic_encode ;
typedef  int /*<<< orphan*/  generic_decode ;

/* Variables and functions */
 scalar_t__ asprintf (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  cmp_universal_string ; 
 scalar_t__ der_free_universal_string ; 
 scalar_t__ der_get_universal_string ; 
 scalar_t__ der_length_universal_string ; 
 scalar_t__ der_put_universal_string ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int generic_test (struct test_case*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  universal_d1 ; 
 int /*<<< orphan*/  universal_d2 ; 

__attribute__((used)) static int
test_universal_string (void)
{
    heim_universal_string s1 = { 1, universal_d1 };
    heim_universal_string s2 = { 2, universal_d2 };

    struct test_case tests[] = {
	{NULL, 4, "\x00\x00\x00\x20"},
	{NULL, 8, "\x00\x00\x00\x20\x00\x00\x00\x20"}
    };
    int ntests = sizeof(tests) / sizeof(*tests);
    int ret;

    tests[0].val = &s1;
    if (asprintf (&tests[0].name, "a universal string") < 0)
	errx(1, "malloc");
    if (tests[0].name == NULL)
	errx(1, "malloc");
    tests[1].val = &s2;
    if (asprintf (&tests[1].name, "second universal string") < 0)
	errx(1, "malloc");
    if (tests[1].name == NULL)
	errx(1, "malloc");

    ret = generic_test (tests, ntests, sizeof(heim_universal_string),
			(generic_encode)der_put_universal_string,
			(generic_length)der_length_universal_string,
			(generic_decode)der_get_universal_string,
			(generic_free)der_free_universal_string,
			cmp_universal_string,
			NULL);
    free(tests[0].name);
    free(tests[1].name);
    return ret;
}