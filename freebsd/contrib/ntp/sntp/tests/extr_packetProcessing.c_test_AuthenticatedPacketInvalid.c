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
struct TYPE_7__ {int* exten; } ;
struct TYPE_6__ {TYPE_3__ p; } ;
struct TYPE_5__ {int /*<<< orphan*/  p; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTHENTICATION ; 
 int /*<<< orphan*/  ENABLED_OPT (int /*<<< orphan*/ ) ; 
 scalar_t__ KEY_MAC_LEN ; 
 int LEN_PKT_NOMAC ; 
 scalar_t__ MAX_MD5_LEN ; 
 int /*<<< orphan*/  MODE_SERVER ; 
 int /*<<< orphan*/  PrepareAuthenticationTestMD5 (int,int,char*) ; 
 int /*<<< orphan*/  SERVER_AUTH_FAIL ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_TRUE (int /*<<< orphan*/ ) ; 
 int htonl (int) ; 
 int /*<<< orphan*/  key_ptr ; 
 int make_mac (TYPE_3__*,int,scalar_t__,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  process_pkt (TYPE_3__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 TYPE_2__ testpkt ; 
 int /*<<< orphan*/  testsock ; 
 TYPE_1__ testspkt ; 

void
test_AuthenticatedPacketInvalid(void)
{
	/* Activate authentication option */
	PrepareAuthenticationTestMD5(50, 9, "123456789");
	TEST_ASSERT_TRUE(ENABLED_OPT(AUTHENTICATION));
	
	/* Prepare the packet. */
	int pkt_len = LEN_PKT_NOMAC;

	testpkt.p.exten[0] = htonl(50);
	int mac_len = make_mac(&testpkt.p, pkt_len,
			       MAX_MD5_LEN - KEY_MAC_LEN, key_ptr,
			       &testpkt.p.exten[1]);

	pkt_len += 4 + mac_len;

	/* Now, alter the MAC so it becomes invalid. */
	testpkt.p.exten[1] += 1;

	TEST_ASSERT_EQUAL(SERVER_AUTH_FAIL,
			  process_pkt(&testpkt.p, &testsock, pkt_len,
				      MODE_SERVER, &testspkt.p, "UnitTest"));
}