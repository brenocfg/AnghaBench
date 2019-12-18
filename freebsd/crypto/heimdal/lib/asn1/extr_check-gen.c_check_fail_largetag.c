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
typedef  int /*<<< orphan*/  TESTLargeTag ;

/* Variables and functions */
 scalar_t__ decode_TESTLargeTag ; 
 int generic_decode_fail (struct test_case*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
check_fail_largetag(void)
{
    struct test_case tests[] = {
	{NULL, 14, "\x30\x0c\xbf\x87\xff\xff\xff\xff\xff\x7f\x03\x02\x01\x01",
	 "tag overflow"},
	{NULL, 0, "", "empty buffer"},
	{NULL, 7, "\x30\x05\xa1\x03\x02\x02\x01",
	 "one too short" },
	{NULL, 7, "\x30\x04\xa1\x03\x02\x02\x01"
	 "two too short" },
	{NULL, 7, "\x30\x03\xa1\x03\x02\x02\x01",
	 "three too short" },
	{NULL, 7, "\x30\x02\xa1\x03\x02\x02\x01",
	 "four too short" },
	{NULL, 7, "\x30\x01\xa1\x03\x02\x02\x01",
	 "five too short" },
	{NULL, 7, "\x30\x00\xa1\x03\x02\x02\x01",
	 "six too short" },
	{NULL, 7, "\x30\x05\xa1\x04\x02\x02\x01",
	 "inner one too long" },
	{NULL, 7, "\x30\x00\xa1\x02\x02\x02\x01",
	 "inner one too short" },
	{NULL, 8, "\x30\x05\xbf\x7f\x03\x02\x02\x01",
	 "inner one too short"},
	{NULL, 8, "\x30\x06\xbf\x64\x03\x02\x01\x01",
	 "wrong tag"},
	{NULL, 10, "\x30\x08\xbf\x9a\x9b\x38\x03\x02\x01\x01",
	 "still wrong tag"}
    };
    int ntests = sizeof(tests) / sizeof(*tests);

    return generic_decode_fail(tests, ntests, sizeof(TESTLargeTag),
			       (generic_decode)decode_TESTLargeTag);
}