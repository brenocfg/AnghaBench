#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tests ;
struct test_case {int member_1; char* member_2; char* member_3; TYPE_1__* val; int /*<<< orphan*/ * member_0; } ;
typedef  int /*<<< orphan*/  lt1 ;
typedef  int /*<<< orphan*/  generic_length ;
typedef  int /*<<< orphan*/  generic_free ;
typedef  int /*<<< orphan*/  generic_encode ;
typedef  int /*<<< orphan*/  generic_decode ;
typedef  int /*<<< orphan*/  generic_copy ;
struct TYPE_3__ {int foo; int bar; } ;
typedef  TYPE_1__ TESTLargeTag ;

/* Variables and functions */
 int /*<<< orphan*/  cmp_TESTLargeTag ; 
 scalar_t__ copy_TESTLargeTag ; 
 scalar_t__ decode_TESTLargeTag ; 
 scalar_t__ encode_TESTLargeTag ; 
 scalar_t__ free_TESTLargeTag ; 
 int generic_test (struct test_case*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ length_TESTLargeTag ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
test_large_tag (void)
{
    struct test_case tests[] = {
	{ NULL,  15,  "\x30\x0d\xbf\x7f\x03\x02\x01\x01\xbf\x81\x00\x03\x02\x01\x02", "large tag 1" }
    };

    int ntests = sizeof(tests) / sizeof(*tests);
    TESTLargeTag lt1;

    memset(&lt1, 0, sizeof(lt1));
    lt1.foo = 1;
    lt1.bar = 2;

    tests[0].val = &lt1;

    return generic_test (tests, ntests, sizeof(TESTLargeTag),
			 (generic_encode)encode_TESTLargeTag,
			 (generic_length)length_TESTLargeTag,
			 (generic_decode)decode_TESTLargeTag,
			 (generic_free)free_TESTLargeTag,
			 cmp_TESTLargeTag,
			 (generic_copy)copy_TESTLargeTag);
}