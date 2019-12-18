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
struct TYPE_4__ {int /*<<< orphan*/  li_vn_mode; } ;
struct TYPE_3__ {TYPE_2__ p; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTHENTICATION ; 
 int /*<<< orphan*/  ENABLED_OPT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LEAP_NOWARNING ; 
 int /*<<< orphan*/  LEN_PKT_NOMAC ; 
 int /*<<< orphan*/  MODE_BROADCAST ; 
 int /*<<< orphan*/  NTP_VERSION ; 
 int /*<<< orphan*/  PKT_LI_VN_MODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_FALSE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_pkt (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 TYPE_1__ testpkt ; 
 int /*<<< orphan*/  testsock ; 

void
test_AcceptNoSentPacketBroadcastMode(void)
{
	TEST_ASSERT_FALSE(ENABLED_OPT(AUTHENTICATION));

	testpkt.p.li_vn_mode = PKT_LI_VN_MODE(LEAP_NOWARNING,
					      NTP_VERSION,
					      MODE_BROADCAST);

	TEST_ASSERT_EQUAL(LEN_PKT_NOMAC,
		  process_pkt(&testpkt.p, &testsock, LEN_PKT_NOMAC,
			      MODE_BROADCAST, NULL, "UnitTest"));
}