#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  p; } ;
struct TYPE_3__ {int /*<<< orphan*/  p; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTHENTICATION ; 
 int /*<<< orphan*/  ActivateOption (char*,char*) ; 
 int /*<<< orphan*/  ENABLED_OPT (int /*<<< orphan*/ ) ; 
 int LEN_PKT_NOMAC ; 
 int /*<<< orphan*/  MODE_SERVER ; 
 int /*<<< orphan*/  SERVER_AUTH_FAIL ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_TRUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_pkt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 TYPE_2__ testpkt ; 
 int /*<<< orphan*/  testsock ; 
 TYPE_1__ testspkt ; 

void
test_CryptoNAKPacketReject(void)
{
	/* Activate authentication option */
	ActivateOption("-a", "123");
	TEST_ASSERT_TRUE(ENABLED_OPT(AUTHENTICATION));

	int pkt_len = LEN_PKT_NOMAC + 4; /* + 4 byte MAC = Crypto-NAK */

	TEST_ASSERT_EQUAL(SERVER_AUTH_FAIL,
			  process_pkt(&testpkt.p, &testsock, pkt_len,
				      MODE_SERVER, &testspkt.p, "UnitTest"));
}