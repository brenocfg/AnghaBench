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
 int /*<<< orphan*/  assert_ng_parses (char*,char*,char*) ; 
 int /*<<< orphan*/  assert_pkt_fails (char*) ; 

void test_transports_smart_packet__ng_pkt(void)
{
	/* TODO: same as for ok pkt */
	assert_pkt_fails("0007ng\n");
	assert_pkt_fails("0008ng \n");
	assert_pkt_fails("000Bng ref\n");
	assert_pkt_fails("000Bng ref\n");
	/* TODO: is this a valid packet line? Probably not. */
	assert_ng_parses("000Ang  x\n", "", "x");
	assert_ng_parses("000Fng ref msg\n", "ref", "msg");
	assert_ng_parses("000Fng ref msg\n", "ref", "msg");
}