#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * exten; } ;
struct TYPE_6__ {TYPE_3__ p; } ;
struct TYPE_5__ {int /*<<< orphan*/  p; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTHENTICATION ; 
 int /*<<< orphan*/  ENABLED_OPT (int /*<<< orphan*/ ) ; 
 scalar_t__ KEY_MAC_LEN ; 
 int LEN_PKT_NOMAC ; 
 int /*<<< orphan*/  MAX_MDG_LEN ; 
 int /*<<< orphan*/  MODE_SERVER ; 
 int /*<<< orphan*/  PrepareAuthenticationTest (int,int,char*,char*) ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_TRUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  key_ptr ; 
 int make_mac (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_pkt (TYPE_3__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 TYPE_2__ testpkt ; 
 int /*<<< orphan*/  testsock ; 
 TYPE_1__ testspkt ; 

void
test_CorrectAuthenticatedPacketSHA1(void)
{
	PrepareAuthenticationTest(20, 15, "SHA1", "abcdefghijklmno");
	TEST_ASSERT_TRUE(ENABLED_OPT(AUTHENTICATION));

	int pkt_len = LEN_PKT_NOMAC;

	/* Prepare the packet. */
	testpkt.p.exten[0] = htonl(20);
	int mac_len = make_mac(&testpkt.p, pkt_len,
			       MAX_MDG_LEN, key_ptr,
			       &testpkt.p.exten[1]);

	pkt_len += KEY_MAC_LEN + mac_len;

	TEST_ASSERT_EQUAL(pkt_len,
			  process_pkt(&testpkt.p, &testsock, pkt_len,
				      MODE_SERVER, &testspkt.p, "UnitTest"));
}