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
typedef  TYPE_1__ heim_oid ;
typedef  int /*<<< orphan*/  generic_length ;
typedef  int /*<<< orphan*/  generic_free ;
typedef  int /*<<< orphan*/  generic_encode ;
typedef  int /*<<< orphan*/  generic_decode ;

/* Variables and functions */
 scalar_t__ asprintf (int /*<<< orphan*/ **,char*,int) ; 
 scalar_t__ der_free_oid ; 
 scalar_t__ der_get_oid ; 
 scalar_t__ der_length_oid ; 
 scalar_t__ der_put_oid ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int generic_test (struct test_case*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oid_comp1 ; 
 int /*<<< orphan*/  oid_comp2 ; 
 int /*<<< orphan*/  oid_comp3 ; 
 int /*<<< orphan*/  oid_comp4 ; 
 int /*<<< orphan*/  test_cmp_oid ; 

__attribute__((used)) static int
test_oid (void)
{
    struct test_case tests[] = {
	{NULL, 2, "\x29\x01"},
	{NULL, 1, "\x29"},
	{NULL, 2, "\xff\x01"},
	{NULL, 1, "\xff"}
    };
    heim_oid values[] = {
	{ 3, oid_comp1 },
	{ 2, oid_comp2 },
	{ 3, oid_comp3 },
	{ 2, oid_comp4 }
    };
    int i, ret;
    int ntests = sizeof(tests) / sizeof(*tests);

    for (i = 0; i < ntests; ++i) {
	tests[i].val = &values[i];
	if (asprintf (&tests[i].name, "oid %d", i) < 0)
	    errx(1, "malloc");
	if (tests[i].name == NULL)
	    errx(1, "malloc");
    }

    ret = generic_test (tests, ntests, sizeof(heim_oid),
			(generic_encode)der_put_oid,
			(generic_length)der_length_oid,
			(generic_decode)der_get_oid,
			(generic_free)der_free_oid,
			test_cmp_oid,
			NULL);
    for (i = 0; i < ntests; ++i)
	free(tests[i].name);
    return ret;
}