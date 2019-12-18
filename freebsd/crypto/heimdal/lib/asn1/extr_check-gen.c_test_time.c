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
struct test_case {int member_1; char* member_2; char* member_3; int* val; int /*<<< orphan*/ * member_0; } ;
typedef  int /*<<< orphan*/  generic_length ;
typedef  int /*<<< orphan*/  generic_free ;
typedef  int /*<<< orphan*/  generic_encode ;
typedef  int /*<<< orphan*/  generic_decode ;
typedef  int /*<<< orphan*/  generic_copy ;
typedef  int KerberosTime ;

/* Variables and functions */
 int /*<<< orphan*/  cmp_KerberosTime ; 
 scalar_t__ copy_KerberosTime ; 
 scalar_t__ decode_KerberosTime ; 
 scalar_t__ encode_KerberosTime ; 
 scalar_t__ free_KerberosTime ; 
 int generic_test (struct test_case*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ length_KerberosTime ; 

__attribute__((used)) static int
test_time (void)
{
    struct test_case tests[] = {
	{ NULL,  17,
	  "\x18\x0f\x31\x39\x37\x30\x30\x31\x30\x31\x30\x31\x31\x38\x33\x31"
	  "\x5a",
	  "time 1" },
	{ NULL,  17,
	  "\x18\x0f\x32\x30\x30\x39\x30\x35\x32\x34\x30\x32\x30\x32\x34\x30"
	  "\x5a"
	  "time 2" }
    };

    int ntests = sizeof(tests) / sizeof(*tests);
    KerberosTime times[] = {
	4711,
	1243130560
    };

    tests[0].val = &times[0];
    tests[1].val = &times[1];

    return generic_test (tests, ntests, sizeof(KerberosTime),
			 (generic_encode)encode_KerberosTime,
			 (generic_length)length_KerberosTime,
			 (generic_decode)decode_KerberosTime,
			 (generic_free)free_KerberosTime,
			 cmp_KerberosTime,
			 (generic_copy)copy_KerberosTime);
}