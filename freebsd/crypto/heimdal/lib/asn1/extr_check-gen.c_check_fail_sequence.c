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
typedef  int /*<<< orphan*/  TESTSeq ;

/* Variables and functions */
 scalar_t__ decode_TESTSeq ; 
 int generic_decode_fail (struct test_case*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
check_fail_sequence(void)
{
    struct test_case tests[] = {
	{NULL, 0, "", "empty buffer"},
	{NULL, 24,
	 "\x30\x16\xa0\x03\x02\x01\x01\xa1\x08\x30\x06\xbf\x7f\x03\x02\x01\x01"
	 "\x02\x01\x01\xa2\x03\x02\x01\x01"
	 "missing one byte from the end, internal length ok"},
	{NULL, 25,
	 "\x30\x18\xa0\x03\x02\x01\x01\xa1\x08\x30\x06\xbf\x7f\x03\x02\x01\x01"
	 "\x02\x01\x01\xa2\x03\x02\x01\x01",
	 "inner length one byte too long"},
	{NULL, 24,
	 "\x30\x17\xa0\x03\x02\x01\x01\xa1\x08\x30\x06\xbf\x7f\x03\x02\x01"
	 "\x01\x02\x01\x01\xa2\x03\x02\x01\x01",
	 "correct buffer but missing one too short"}
    };
    int ntests = sizeof(tests) / sizeof(*tests);

    return generic_decode_fail(tests, ntests, sizeof(TESTSeq),
			       (generic_decode)decode_TESTSeq);
}