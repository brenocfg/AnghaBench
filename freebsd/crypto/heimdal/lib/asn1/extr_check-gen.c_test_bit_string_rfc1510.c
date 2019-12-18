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
typedef  int /*<<< orphan*/  tf4 ;
typedef  int /*<<< orphan*/  tf3 ;
typedef  int /*<<< orphan*/  tf2 ;
typedef  int /*<<< orphan*/  tf1 ;
typedef  int /*<<< orphan*/  tests ;
struct test_case {int member_1; char* member_2; char* member_3; TYPE_1__* val; int /*<<< orphan*/ * member_0; } ;
typedef  int /*<<< orphan*/  generic_length ;
typedef  int /*<<< orphan*/  generic_free ;
typedef  int /*<<< orphan*/  generic_encode ;
typedef  int /*<<< orphan*/  generic_decode ;
typedef  int /*<<< orphan*/  generic_copy ;
struct TYPE_3__ {int reserved; int forwardable; int pre_authent; } ;
typedef  TYPE_1__ TicketFlags ;

/* Variables and functions */
 int /*<<< orphan*/  cmp_TicketFlags ; 
 scalar_t__ copy_TicketFlags ; 
 scalar_t__ decode_TicketFlags ; 
 scalar_t__ encode_TicketFlags ; 
 scalar_t__ free_TicketFlags ; 
 int generic_test (struct test_case*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ length_TicketFlags ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
test_bit_string_rfc1510 (void)
{
    struct test_case tests[] = {
	{ NULL, 7,
	  "\x03\x05\x00\x80\x00\x00\x00",
	  "TF bitstring 1"
	},
	{ NULL, 7,
	  "\x03\x05\x00\x40\x20\x00\x00",
	  "TF bitstring 2"
	},
	{ NULL, 7,
	  "\x03\x05\x00\x00\x20\x00\x00",
	  "TF bitstring 3"
	},
	{ NULL, 7,
	  "\x03\x05\x00\x00\x00\x00\x00",
	  "TF bitstring 4"
	}
    };

    int ntests = sizeof(tests) / sizeof(*tests);
    TicketFlags tf1, tf2, tf3, tf4;

    memset(&tf1, 0, sizeof(tf1));
    tf1.reserved = 1;
    tests[0].val = &tf1;

    memset(&tf2, 0, sizeof(tf2));
    tf2.forwardable = 1;
    tf2.pre_authent = 1;
    tests[1].val = &tf2;

    memset(&tf3, 0, sizeof(tf3));
    tf3.pre_authent = 1;
    tests[2].val = &tf3;

    memset(&tf4, 0, sizeof(tf4));
    tests[3].val = &tf4;


    return generic_test (tests, ntests, sizeof(TicketFlags),
			 (generic_encode)encode_TicketFlags,
			 (generic_length)length_TicketFlags,
			 (generic_decode)decode_TicketFlags,
			 (generic_free)free_TicketFlags,
			 cmp_TicketFlags,
			 (generic_copy)copy_TicketFlags);
}