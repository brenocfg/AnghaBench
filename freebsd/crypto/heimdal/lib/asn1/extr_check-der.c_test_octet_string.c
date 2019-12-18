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
struct TYPE_2__ {int member_0; char* member_1; } ;
typedef  TYPE_1__ heim_octet_string ;
typedef  int /*<<< orphan*/  generic_length ;
typedef  int /*<<< orphan*/  generic_free ;
typedef  int /*<<< orphan*/  generic_encode ;
typedef  int /*<<< orphan*/  generic_decode ;

/* Variables and functions */
 scalar_t__ asprintf (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  cmp_octet_string ; 
 scalar_t__ der_free_octet_string ; 
 scalar_t__ der_get_octet_string ; 
 scalar_t__ der_length_octet_string ; 
 scalar_t__ der_put_octet_string ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int generic_test (struct test_case*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
test_octet_string (void)
{
    heim_octet_string s1 = {8, "\x01\x23\x45\x67\x89\xab\xcd\xef"};

    struct test_case tests[] = {
	{NULL, 8, "\x01\x23\x45\x67\x89\xab\xcd\xef"}
    };
    int ntests = sizeof(tests) / sizeof(*tests);
    int ret;

    tests[0].val = &s1;
    if (asprintf (&tests[0].name, "a octet string") < 0)
	errx(1, "malloc");
    if (tests[0].name == NULL)
	errx(1, "malloc");

    ret = generic_test (tests, ntests, sizeof(heim_octet_string),
			(generic_encode)der_put_octet_string,
			(generic_length)der_length_octet_string,
			(generic_decode)der_get_octet_string,
			(generic_free)der_free_octet_string,
			cmp_octet_string,
			NULL);
    free(tests[0].name);
    return ret;
}