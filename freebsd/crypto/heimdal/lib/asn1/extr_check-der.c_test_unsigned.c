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
struct test_case {int member_1; char* member_2; unsigned int* val; int /*<<< orphan*/ * name; int /*<<< orphan*/ * member_0; } ;
typedef  int /*<<< orphan*/  generic_length ;
typedef  int /*<<< orphan*/  generic_free ;
typedef  int /*<<< orphan*/  generic_encode ;
typedef  int /*<<< orphan*/  generic_decode ;

/* Variables and functions */
 scalar_t__ asprintf (int /*<<< orphan*/ **,char*,unsigned int) ; 
 int /*<<< orphan*/  cmp_unsigned ; 
 scalar_t__ der_get_unsigned ; 
 scalar_t__ der_length_unsigned ; 
 scalar_t__ der_put_unsigned ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int generic_test (struct test_case*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
test_unsigned (void)
{
    struct test_case tests[] = {
	{NULL, 1, "\x00"},
	{NULL, 1, "\x7f"},
	{NULL, 2, "\x00\x80"},
	{NULL, 2, "\x01\x00"},
	{NULL, 2, "\x02\x00"},
	{NULL, 3, "\x00\x80\x00"},
	{NULL, 5, "\x00\x80\x00\x00\x00"},
	{NULL, 4, "\x7f\xff\xff\xff"}
    };

    unsigned int values[] = {0, 127, 128, 256, 512, 32768,
			     0x80000000, 0x7fffffff};
    int i, ret;
    int ntests = sizeof(tests) / sizeof(*tests);

    for (i = 0; i < ntests; ++i) {
	tests[i].val = &values[i];
	if (asprintf (&tests[i].name, "unsigned %u", values[i]) < 0)
	    errx(1, "malloc");
	if (tests[i].name == NULL)
	    errx(1, "malloc");
    }

    ret = generic_test (tests, ntests, sizeof(int),
			(generic_encode)der_put_unsigned,
			(generic_length)der_length_unsigned,
			(generic_decode)der_get_unsigned,
			(generic_free)NULL,
			cmp_unsigned,
			NULL);
    for (i = 0; i < ntests; ++i)
	free (tests[i].name);
    return ret;
}