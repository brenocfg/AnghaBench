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
 int /*<<< orphan*/  GIT_ACK_COMMON ; 
 int /*<<< orphan*/  GIT_ACK_CONTINUE ; 
 int /*<<< orphan*/  GIT_ACK_READY ; 
 int /*<<< orphan*/  assert_ack_parses (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_pkt_fails (char*) ; 

void test_transports_smart_packet__ack_pkt(void)
{
	assert_ack_parses("0030ACK 0000000000000000000000000000000000000000",
			  "0000000000000000000000000000000000000000", 0);
	assert_ack_parses("0039ACK 0000000000000000000000000000000000000000 continue",
			  "0000000000000000000000000000000000000000",
			  GIT_ACK_CONTINUE);
	assert_ack_parses("0037ACK 0000000000000000000000000000000000000000 common",
			  "0000000000000000000000000000000000000000",
			  GIT_ACK_COMMON);
	assert_ack_parses("0037ACK 0000000000000000000000000000000000000000 ready",
			  "0000000000000000000000000000000000000000",
			  GIT_ACK_READY);

	/* these should fail as they don't have OIDs */
	assert_pkt_fails("0007ACK");
	assert_pkt_fails("0008ACK ");

	/* this one is missing a space and should thus fail */
	assert_pkt_fails("0036ACK00000000000000000x0000000000000000000000 ready");

	/* the following ones have invalid OIDs and should thus fail */
	assert_pkt_fails("0037ACK 00000000000000000x0000000000000000000000 ready");
	assert_pkt_fails("0036ACK 000000000000000000000000000000000000000 ready");
	assert_pkt_fails("0036ACK 00000000000000000x0000000000000000000000ready");

	/* this one has an invalid status and should thus fail */
	assert_pkt_fails("0036ACK 0000000000000000000000000000000000000000 read");
}