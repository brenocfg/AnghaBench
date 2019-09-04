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
 int /*<<< orphan*/  assert_error_parses (char*,char*,int) ; 
 int /*<<< orphan*/  assert_pkt_fails (char*) ; 

void test_transports_smart_packet__sideband_err_pkt(void)
{
	assert_pkt_fails("0001\3");
	assert_error_parses("0005\3", "", 0);
	assert_pkt_fails("0009\3o");
	assert_error_parses("0009\3data", "data", 4);
	assert_error_parses("000a\3data", "data", 5);
}