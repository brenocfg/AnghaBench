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
struct TYPE_2__ {char* member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ heim_bit_string ;
typedef  int /*<<< orphan*/  generic_length ;
typedef  int /*<<< orphan*/  generic_free ;
typedef  int /*<<< orphan*/  generic_encode ;
typedef  int /*<<< orphan*/  generic_decode ;

/* Variables and functions */
 scalar_t__ asprintf (int /*<<< orphan*/ **,char*,int) ; 
 scalar_t__ der_free_bit_string ; 
 scalar_t__ der_get_bit_string ; 
 scalar_t__ der_length_bit_string ; 
 scalar_t__ der_put_bit_string ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int generic_test (struct test_case*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_cmp_bit_string ; 

__attribute__((used)) static int
test_bit_string (void)
{
    struct test_case tests[] = {
	{NULL, 1, "\x00"}
    };
    heim_bit_string values[] = {
	{ 0, "" }
    };
    int i, ret;
    int ntests = sizeof(tests) / sizeof(*tests);

    for (i = 0; i < ntests; ++i) {
	tests[i].val = &values[i];
	if (asprintf (&tests[i].name, "bit_string %d", i) < 0)
	    errx(1, "malloc");
	if (tests[i].name == NULL)
	    errx(1, "malloc");
    }

    ret = generic_test (tests, ntests, sizeof(heim_bit_string),
			(generic_encode)der_put_bit_string,
			(generic_length)der_length_bit_string,
			(generic_decode)der_get_bit_string,
			(generic_free)der_free_bit_string,
			test_cmp_bit_string,
			NULL);
    for (i = 0; i < ntests; ++i)
	free(tests[i].name);
    return ret;
}