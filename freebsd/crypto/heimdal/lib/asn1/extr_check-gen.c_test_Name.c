#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tests ;
struct test_case {int member_1; char* member_2; char* member_3; TYPE_8__* val; int /*<<< orphan*/ * member_0; } ;
typedef  int /*<<< orphan*/  rdn2 ;
typedef  int /*<<< orphan*/  rdn1 ;
typedef  int /*<<< orphan*/  generic_length ;
typedef  int /*<<< orphan*/  generic_free ;
typedef  int /*<<< orphan*/  generic_encode ;
typedef  int /*<<< orphan*/  generic_decode ;
typedef  int /*<<< orphan*/  generic_copy ;
typedef  int /*<<< orphan*/  cmp_L ;
typedef  int /*<<< orphan*/  cmp_CN ;
typedef  int /*<<< orphan*/  atv2 ;
typedef  int /*<<< orphan*/  atv1 ;
struct TYPE_13__ {char* data; int length; } ;
struct TYPE_14__ {TYPE_4__ printableString; } ;
struct TYPE_15__ {TYPE_5__ u; void* element; } ;
struct TYPE_12__ {int length; unsigned int* components; } ;
struct TYPE_18__ {TYPE_6__ value; TYPE_3__ type; } ;
struct TYPE_10__ {int len; TYPE_7__* val; } ;
struct TYPE_11__ {TYPE_1__ rdnSequence; } ;
struct TYPE_17__ {TYPE_2__ u; void* element; } ;
struct TYPE_16__ {int len; TYPE_9__* val; } ;
typedef  TYPE_7__ RelativeDistinguishedName ;
typedef  TYPE_8__ Name ;
typedef  TYPE_9__ AttributeTypeAndValue ;

/* Variables and functions */
 void* choice_DirectoryString_printableString ; 
 void* choice_Name_rdnSequence ; 
 int /*<<< orphan*/  cmp_Name ; 
 scalar_t__ copy_Name ; 
 scalar_t__ decode_Name ; 
 scalar_t__ encode_Name ; 
 scalar_t__ free_Name ; 
 int generic_test (struct test_case*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ length_Name ; 

__attribute__((used)) static int
test_Name (void)
{
    struct test_case tests[] = {
	{ NULL, 35,
	  "\x30\x21\x31\x1f\x30\x0b\x06\x03\x55\x04\x03\x13\x04\x4c\x6f\x76"
	  "\x65\x30\x10\x06\x03\x55\x04\x07\x13\x09\x53\x54\x4f\x43\x4b\x48"
	  "\x4f\x4c\x4d",
	  "Name CN=Love+L=STOCKHOLM"
	},
	{ NULL, 35,
	  "\x30\x21\x31\x1f\x30\x0b\x06\x03\x55\x04\x03\x13\x04\x4c\x6f\x76"
	  "\x65\x30\x10\x06\x03\x55\x04\x07\x13\x09\x53\x54\x4f\x43\x4b\x48"
	  "\x4f\x4c\x4d",
	  "Name L=STOCKHOLM+CN=Love"
	}
    };

    int ntests = sizeof(tests) / sizeof(*tests);
    Name n1, n2;
    RelativeDistinguishedName rdn1[1];
    RelativeDistinguishedName rdn2[1];
    AttributeTypeAndValue atv1[2];
    AttributeTypeAndValue atv2[2];
    unsigned cmp_CN[] = { 2, 5, 4, 3 };
    unsigned cmp_L[] = { 2, 5, 4, 7 };

    /* n1 */
    n1.element = choice_Name_rdnSequence;
    n1.u.rdnSequence.val = rdn1;
    n1.u.rdnSequence.len = sizeof(rdn1)/sizeof(rdn1[0]);
    rdn1[0].val = atv1;
    rdn1[0].len = sizeof(atv1)/sizeof(atv1[0]);

    atv1[0].type.length = sizeof(cmp_CN)/sizeof(cmp_CN[0]);
    atv1[0].type.components = cmp_CN;
    atv1[0].value.element = choice_DirectoryString_printableString;
    atv1[0].value.u.printableString.data = "Love";
    atv1[0].value.u.printableString.length = 4;

    atv1[1].type.length = sizeof(cmp_L)/sizeof(cmp_L[0]);
    atv1[1].type.components = cmp_L;
    atv1[1].value.element = choice_DirectoryString_printableString;
    atv1[1].value.u.printableString.data = "STOCKHOLM";
    atv1[1].value.u.printableString.length = 9;

    /* n2 */
    n2.element = choice_Name_rdnSequence;
    n2.u.rdnSequence.val = rdn2;
    n2.u.rdnSequence.len = sizeof(rdn2)/sizeof(rdn2[0]);
    rdn2[0].val = atv2;
    rdn2[0].len = sizeof(atv2)/sizeof(atv2[0]);

    atv2[0].type.length = sizeof(cmp_L)/sizeof(cmp_L[0]);
    atv2[0].type.components = cmp_L;
    atv2[0].value.element = choice_DirectoryString_printableString;
    atv2[0].value.u.printableString.data = "STOCKHOLM";
    atv2[0].value.u.printableString.length = 9;

    atv2[1].type.length = sizeof(cmp_CN)/sizeof(cmp_CN[0]);
    atv2[1].type.components = cmp_CN;
    atv2[1].value.element = choice_DirectoryString_printableString;
    atv2[1].value.u.printableString.data = "Love";
    atv2[1].value.u.printableString.length = 4;

    /* */
    tests[0].val = &n1;
    tests[1].val = &n2;

    return generic_test (tests, ntests, sizeof(Name),
			 (generic_encode)encode_Name,
			 (generic_length)length_Name,
			 (generic_decode)decode_Name,
			 (generic_free)free_Name,
			 cmp_Name,
			 (generic_copy)copy_Name);
}