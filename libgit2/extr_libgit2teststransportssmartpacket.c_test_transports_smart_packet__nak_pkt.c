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
 int /*<<< orphan*/  assert_nak_parses (char*) ; 
 int /*<<< orphan*/  assert_pkt_fails (char*) ; 

void test_transports_smart_packet__nak_pkt(void)
{
	assert_nak_parses("0007NAK");
	assert_pkt_fails("0007NaK");
	assert_pkt_fails("0007nak");
	assert_nak_parses("0007NAKfoobar");
	assert_pkt_fails("0007nakfoobar");
	assert_pkt_fails("0007 NAK");
}