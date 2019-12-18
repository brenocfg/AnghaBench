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
typedef  int /*<<< orphan*/  ku4 ;
typedef  int /*<<< orphan*/  ku3 ;
typedef  int /*<<< orphan*/  ku2 ;
typedef  int /*<<< orphan*/  ku1 ;
typedef  int /*<<< orphan*/  generic_length ;
typedef  int /*<<< orphan*/  generic_free ;
typedef  int /*<<< orphan*/  generic_encode ;
typedef  int /*<<< orphan*/  generic_decode ;
typedef  int /*<<< orphan*/  generic_copy ;
struct TYPE_3__ {int digitalSignature; int keyEncipherment; int decipherOnly; } ;
typedef  TYPE_1__ KeyUsage ;

/* Variables and functions */
 int /*<<< orphan*/  cmp_KeyUsage ; 
 scalar_t__ copy_KeyUsage ; 
 scalar_t__ decode_KeyUsage ; 
 scalar_t__ encode_KeyUsage ; 
 scalar_t__ free_KeyUsage ; 
 int generic_test (struct test_case*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ length_KeyUsage ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
test_bit_string (void)
{
    struct test_case tests[] = {
	{ NULL, 4,
	  "\x03\x02\x07\x80",
	  "bitstring 1"
	},
	{ NULL, 4,
	  "\x03\x02\x05\xa0",
	  "bitstring 2"
	},
	{ NULL, 5,
	  "\x03\x03\x07\x00\x80",
	  "bitstring 3"
	},
	{ NULL, 3,
	  "\x03\x01\x00",
	  "bitstring 4"
	}
    };

    int ntests = sizeof(tests) / sizeof(*tests);
    KeyUsage ku1, ku2, ku3, ku4;

    memset(&ku1, 0, sizeof(ku1));
    ku1.digitalSignature = 1;
    tests[0].val = &ku1;

    memset(&ku2, 0, sizeof(ku2));
    ku2.digitalSignature = 1;
    ku2.keyEncipherment = 1;
    tests[1].val = &ku2;

    memset(&ku3, 0, sizeof(ku3));
    ku3.decipherOnly = 1;
    tests[2].val = &ku3;

    memset(&ku4, 0, sizeof(ku4));
    tests[3].val = &ku4;


    return generic_test (tests, ntests, sizeof(KeyUsage),
			 (generic_encode)encode_KeyUsage,
			 (generic_length)length_KeyUsage,
			 (generic_decode)decode_KeyUsage,
			 (generic_free)free_KeyUsage,
			 cmp_KeyUsage,
			 (generic_copy)copy_KeyUsage);
}