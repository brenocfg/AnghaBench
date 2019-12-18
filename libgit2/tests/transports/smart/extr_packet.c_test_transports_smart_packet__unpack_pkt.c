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

/* Variables and functions */
 int /*<<< orphan*/  assert_unpack_parses (char*,int) ; 

void test_transports_smart_packet__unpack_pkt(void)
{
	assert_unpack_parses("000Dunpack ok", 1);
	assert_unpack_parses("000Dunpack ng error-msg", 0);
	/* TODO: the following tests should fail */
	assert_unpack_parses("000Aunpack", 0);
	assert_unpack_parses("0011unpack foobar", 0);
	assert_unpack_parses("0010unpack ng ok", 0);
	assert_unpack_parses("0010unpack okfoo", 1);
}