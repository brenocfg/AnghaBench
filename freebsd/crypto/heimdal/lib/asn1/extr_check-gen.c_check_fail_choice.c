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
typedef  int /*<<< orphan*/  generic_decode ;
typedef  int /*<<< orphan*/  TESTChoice1 ;

/* Variables and functions */
 scalar_t__ decode_TESTChoice1 ; 
 int generic_decode_fail (struct test_case*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
check_fail_choice(void)
{
    struct test_case tests[] = {
	{NULL, 6,
	 "\xa1\x02\x02\x01\x01",
	 "choice one too short"},
	{NULL, 6,
	 "\xa1\x03\x02\x02\x01",
	 "choice one too short inner"}
    };
    int ntests = sizeof(tests) / sizeof(*tests);

    return generic_decode_fail(tests, ntests, sizeof(TESTChoice1),
			       (generic_decode)decode_TESTChoice1);
}