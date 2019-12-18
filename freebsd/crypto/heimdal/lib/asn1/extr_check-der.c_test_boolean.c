#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tests ;
struct test_case {int member_1; char* member_2; int* val; int /*<<< orphan*/ * name; int /*<<< orphan*/ * member_0; } ;
struct TYPE_4__ {scalar_t__ length; } ;
typedef  TYPE_1__ heim_integer ;
typedef  int /*<<< orphan*/  generic_length ;
typedef  int /*<<< orphan*/  generic_free ;
typedef  int /*<<< orphan*/  generic_encode ;
typedef  int /*<<< orphan*/  generic_decode ;

/* Variables and functions */
 scalar_t__ asprintf (int /*<<< orphan*/ **,char*,int) ; 
 int /*<<< orphan*/  der_free_heim_integer (TYPE_1__*) ; 
 scalar_t__ der_get_boolean ; 
 int der_get_heim_integer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,size_t*) ; 
 scalar_t__ der_length_boolean ; 
 scalar_t__ der_put_boolean ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int generic_test (struct test_case*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_cmp_boolean ; 

__attribute__((used)) static int
test_boolean (void)
{
    struct test_case tests[] = {
	{NULL, 1, "\xff"},
	{NULL, 1, "\x00"}
    };

    int values[] = { 1, 0 };
    int i, ret;
    int ntests = sizeof(tests) / sizeof(tests[0]);
    size_t size;
    heim_integer i2;

    for (i = 0; i < ntests; ++i) {
	tests[i].val = &values[i];
	if (asprintf (&tests[i].name, "heim_boolean %d", i) < 0)
	    errx(1, "malloc");
	if (tests[i].name == NULL)
	    errx(1, "malloc");
    }

    ret = generic_test (tests, ntests, sizeof(int),
			(generic_encode)der_put_boolean,
			(generic_length)der_length_boolean,
			(generic_decode)der_get_boolean,
			(generic_free)NULL,
			test_cmp_boolean,
			NULL);
    for (i = 0; i < ntests; ++i)
	free (tests[i].name);
    if (ret)
	return ret;

    /* test zero length integer (BER format) */
    ret = der_get_heim_integer(NULL, 0, &i2, &size);
    if (ret)
	errx(1, "der_get_heim_integer");
    if (i2.length != 0)
	errx(1, "der_get_heim_integer wrong length");
    der_free_heim_integer(&i2);

    return 0;
}