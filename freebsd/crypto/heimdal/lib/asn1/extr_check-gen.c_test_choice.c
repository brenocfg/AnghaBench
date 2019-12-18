#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tests ;
struct test_case {int member_1; char* member_2; char* member_3; TYPE_3__* val; int /*<<< orphan*/ * member_0; } ;
typedef  int /*<<< orphan*/  generic_length ;
typedef  int /*<<< orphan*/  generic_free ;
typedef  int /*<<< orphan*/  generic_encode ;
typedef  int /*<<< orphan*/  generic_decode ;
typedef  int /*<<< orphan*/  generic_copy ;
typedef  int /*<<< orphan*/  c2_2 ;
typedef  int /*<<< orphan*/  c2_1 ;
typedef  int /*<<< orphan*/  c1 ;
struct TYPE_6__ {char* data; int length; } ;
struct TYPE_7__ {int i1; int i2; TYPE_1__ asn1_ellipsis; } ;
struct TYPE_8__ {TYPE_2__ u; int /*<<< orphan*/  element; } ;
typedef  TYPE_3__ TESTChoice2 ;
typedef  TYPE_3__ TESTChoice1 ;

/* Variables and functions */
 int /*<<< orphan*/  choice_TESTChoice1_i1 ; 
 int /*<<< orphan*/  choice_TESTChoice1_i2 ; 
 int /*<<< orphan*/  choice_TESTChoice2_asn1_ellipsis ; 
 int /*<<< orphan*/  cmp_TESTChoice ; 
 scalar_t__ copy_TESTChoice1 ; 
 scalar_t__ copy_TESTChoice2 ; 
 scalar_t__ decode_TESTChoice1 ; 
 scalar_t__ decode_TESTChoice2 ; 
 scalar_t__ encode_TESTChoice1 ; 
 scalar_t__ encode_TESTChoice2 ; 
 scalar_t__ free_TESTChoice1 ; 
 scalar_t__ free_TESTChoice2 ; 
 scalar_t__ generic_test (struct test_case*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ length_TESTChoice1 ; 
 scalar_t__ length_TESTChoice2 ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
test_choice (void)
{
    struct test_case tests[] = {
	{ NULL,  5,  "\xa1\x03\x02\x01\x01", "large choice 1" },
	{ NULL,  5,  "\xa2\x03\x02\x01\x02", "large choice 2" }
    };

    int ret = 0, ntests = sizeof(tests) / sizeof(*tests);
    TESTChoice1 c1;
    TESTChoice1 c2_1;
    TESTChoice2 c2_2;

    memset(&c1, 0, sizeof(c1));
    c1.element = choice_TESTChoice1_i1;
    c1.u.i1 = 1;
    tests[0].val = &c1;

    memset(&c2_1, 0, sizeof(c2_1));
    c2_1.element = choice_TESTChoice1_i2;
    c2_1.u.i2 = 2;
    tests[1].val = &c2_1;

    ret += generic_test (tests, ntests, sizeof(TESTChoice1),
			 (generic_encode)encode_TESTChoice1,
			 (generic_length)length_TESTChoice1,
			 (generic_decode)decode_TESTChoice1,
			 (generic_free)free_TESTChoice1,
			 cmp_TESTChoice,
			 (generic_copy)copy_TESTChoice1);

    memset(&c2_2, 0, sizeof(c2_2));
    c2_2.element = choice_TESTChoice2_asn1_ellipsis;
    c2_2.u.asn1_ellipsis.data = "\xa2\x03\x02\x01\x02";
    c2_2.u.asn1_ellipsis.length = 5;
    tests[1].val = &c2_2;

    ret += generic_test (tests, ntests, sizeof(TESTChoice2),
			 (generic_encode)encode_TESTChoice2,
			 (generic_length)length_TESTChoice2,
			 (generic_decode)decode_TESTChoice2,
			 (generic_free)free_TESTChoice2,
			 cmp_TESTChoice,
			 (generic_copy)copy_TESTChoice2);

    return ret;
}