#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  li_vn_mode; } ;
struct TYPE_5__ {TYPE_3__ p; } ;
struct TYPE_4__ {int /*<<< orphan*/  p; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTHENTICATION ; 
 int /*<<< orphan*/  ENABLED_OPT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LEAP_NOWARNING ; 
 int LEN_PKT_NOMAC ; 
 int /*<<< orphan*/  MODE_CLIENT ; 
 int /*<<< orphan*/  MODE_SERVER ; 
 scalar_t__ NTP_OLDVERSION ; 
 int /*<<< orphan*/  PKT_LI_VN_MODE (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ PKT_VERSION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SERVER_UNUSEABLE ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_FALSE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_TRUE (int) ; 
 int /*<<< orphan*/  process_pkt (TYPE_3__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 TYPE_2__ testpkt ; 
 int /*<<< orphan*/  testsock ; 
 TYPE_1__ testspkt ; 

void
test_ServerVersionTooOld(void)
{
	TEST_ASSERT_FALSE(ENABLED_OPT(AUTHENTICATION));

	testpkt.p.li_vn_mode = PKT_LI_VN_MODE(LEAP_NOWARNING,
					      NTP_OLDVERSION - 1,
					      MODE_CLIENT);
	TEST_ASSERT_TRUE(PKT_VERSION(testpkt.p.li_vn_mode) < NTP_OLDVERSION);

	int pkt_len = LEN_PKT_NOMAC;
	
	TEST_ASSERT_EQUAL(SERVER_UNUSEABLE,
			  process_pkt(&testpkt.p, &testsock, pkt_len,
				      MODE_SERVER, &testspkt.p, "UnitTest"));
}