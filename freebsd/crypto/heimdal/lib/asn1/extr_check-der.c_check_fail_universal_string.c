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
struct test_case {int member_1; char* member_2; char* member_3; int /*<<< orphan*/ * member_0; } ;
typedef  int /*<<< orphan*/  heim_universal_string ;
typedef  int /*<<< orphan*/  generic_decode ;

/* Variables and functions */
 scalar_t__ der_get_universal_string ; 
 int generic_decode_fail (struct test_case*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
check_fail_universal_string(void)
{
    struct test_case tests[] = {
	{NULL, 1, "\x00", "x & 3 == 1 universal string"},
	{NULL, 2, "\x00\x00", "x & 3 == 2 universal string"},
	{NULL, 3, "\x00\x00\x00", "x & 3 == 3 universal string"},
	{NULL, 5, "\x00\x00\x00\x00\x00", "x & 3 == 1 universal string"},
	{NULL, 6, "\x00\x00\x00\x00\x00\x00", "x & 3 == 2 universal string"},
	{NULL, 7, "\x00\x00\x00\x00\x00\x00\x00", "x & 3 == 3 universal string"}
    };
    int ntests = sizeof(tests) / sizeof(*tests);

    return generic_decode_fail(tests, ntests, sizeof(heim_universal_string),
			       (generic_decode)der_get_universal_string);
}