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
struct test_case {int member_1; char* member_2; char* member_3; TYPE_1__* val; int /*<<< orphan*/ * member_0; } ;
typedef  int /*<<< orphan*/  generic_length ;
typedef  int /*<<< orphan*/  generic_free ;
typedef  int /*<<< orphan*/  generic_encode ;
typedef  int /*<<< orphan*/  generic_decode ;
typedef  int /*<<< orphan*/  generic_copy ;
struct TYPE_2__ {int* zero; int* one; } ;
typedef  TYPE_1__ TESTOptional ;

/* Variables and functions */
 int /*<<< orphan*/  cmp_TESTOptional ; 
 scalar_t__ copy_TESTOptional ; 
 scalar_t__ decode_TESTOptional ; 
 scalar_t__ encode_TESTOptional ; 
 scalar_t__ free_TESTOptional ; 
 scalar_t__ generic_test (struct test_case*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ length_TESTOptional ; 

__attribute__((used)) static int
test_optional (void)
{
    struct test_case tests[] = {
	{ NULL,  2,
	  "\x30\x00",
	  "optional 0" },
	{ NULL,  7,
	  "\x30\x05\xa0\x03\x02\x01\x00",
	  "optional 1" },
	{ NULL,  7,
	  "\x30\x05\xa1\x03\x02\x01\x01",
	  "optional 2" },
	{ NULL,  12,
	  "\x30\x0a\xa0\x03\x02\x01\x00\xa1\x03\x02\x01\x01",
	  "optional 3" }
    };

    int ret = 0, ntests = sizeof(tests) / sizeof(*tests);
    TESTOptional c0, c1, c2, c3;
    int zero = 0;
    int one = 1;

    c0.zero = NULL;
    c0.one = NULL;
    tests[0].val = &c0;

    c1.zero = &zero;
    c1.one = NULL;
    tests[1].val = &c1;

    c2.zero = NULL;
    c2.one = &one;
    tests[2].val = &c2;

    c3.zero = &zero;
    c3.one = &one;
    tests[3].val = &c3;

    ret += generic_test (tests, ntests, sizeof(TESTOptional),
			 (generic_encode)encode_TESTOptional,
			 (generic_length)length_TESTOptional,
			 (generic_decode)decode_TESTOptional,
			 (generic_free)free_TESTOptional,
			 cmp_TESTOptional,
			 (generic_copy)copy_TESTOptional);

    return ret;
}