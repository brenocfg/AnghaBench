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
 int /*<<< orphan*/  assert_pkt_fails (char*) ; 

void test_transports_smart_packet__parsing_garbage_fails(void)
{
	assert_pkt_fails("0foobar");
	assert_pkt_fails("00foobar");
	assert_pkt_fails("000foobar");
	assert_pkt_fails("0001");
	assert_pkt_fails("");
	assert_pkt_fails("0");
	assert_pkt_fails("0i00");
	assert_pkt_fails("f");
}