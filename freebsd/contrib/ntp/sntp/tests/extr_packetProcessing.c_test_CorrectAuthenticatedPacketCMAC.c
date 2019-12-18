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
 int /*<<< orphan*/  CMAC ; 
 int /*<<< orphan*/  CMAC_LENGTH ; 
 int /*<<< orphan*/  ENABLED_OPT (int /*<<< orphan*/ ) ; 
 int LEN_PKT_NOMAC ; 
 int /*<<< orphan*/  MAX_MAC_LEN ; 
 int /*<<< orphan*/  MODE_SERVER ; 
 int /*<<< orphan*/  PrepareAuthenticationTest (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_TRUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_IGNORE_MESSAGE (char*) ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  key_ptr ; 
 int make_mac (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_pkt (TYPE_3__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 TYPE_2__ testpkt ; 
 int /*<<< orphan*/  testsock ; 
 TYPE_1__ testspkt ; 

void
test_CorrectAuthenticatedPacketCMAC(void)
{
#if defined(OPENSSL) && defined(ENABLE_CMAC)

	PrepareAuthenticationTest(30, CMAC_LENGTH, CMAC, "abcdefghijklmnop");
	TEST_ASSERT_TRUE(ENABLED_OPT(AUTHENTICATION));

	int pkt_len = LEN_PKT_NOMAC;

	/* Prepare the packet. */
	testpkt.p.exten[0] = htonl(30);
	int mac_len = make_mac(&testpkt.p, pkt_len,
			       MAX_MAC_LEN, key_ptr,
			       &testpkt.p.exten[1]);

	pkt_len += 4 + mac_len;

	TEST_ASSERT_EQUAL(pkt_len,
			  process_pkt(&testpkt.p, &testsock, pkt_len,
				      MODE_SERVER, &testspkt.p, "UnitTest"));

#else
	
	TEST_IGNORE_MESSAGE("OpenSSL CMAC not used, skipping...");
	
#endif	/* OPENSSL */
}