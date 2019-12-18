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
struct timeval {int /*<<< orphan*/  tv_sec; } ;
struct pkt {int /*<<< orphan*/  xmt; int /*<<< orphan*/  ppoll; int /*<<< orphan*/  stratum; int /*<<< orphan*/  li_vn_mode; } ;
typedef  int /*<<< orphan*/  l_fp ;

/* Variables and functions */
 int /*<<< orphan*/  GETTIMEOFDAY (struct timeval*,int /*<<< orphan*/ *) ; 
 scalar_t__ JAN_1970 ; 
 int LEAP_NOTINSYNC ; 
 int LEN_PKT_NOMAC ; 
 int /*<<< orphan*/  LfpEquality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MODE_CLIENT ; 
 int /*<<< orphan*/  NTOHL_FP (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int NTP_VERSION ; 
 int /*<<< orphan*/  PKT_LEAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PKT_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PKT_TO_STRATUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PKT_VERSION (int /*<<< orphan*/ ) ; 
 int STRATUM_UNSPEC ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_TRUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TVTOTS (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  generate_pkt (struct pkt*,struct timeval*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
test_GenerateUnauthenticatedPacket(void)
{
	struct pkt	testpkt;
	struct timeval	xmt;
	l_fp		expected_xmt, actual_xmt;

	GETTIMEOFDAY(&xmt, NULL);
	xmt.tv_sec += JAN_1970;

	TEST_ASSERT_EQUAL(LEN_PKT_NOMAC,
			  generate_pkt(&testpkt, &xmt, 0, NULL));

	TEST_ASSERT_EQUAL(LEAP_NOTINSYNC, PKT_LEAP(testpkt.li_vn_mode));
	TEST_ASSERT_EQUAL(NTP_VERSION, PKT_VERSION(testpkt.li_vn_mode));
	TEST_ASSERT_EQUAL(MODE_CLIENT, PKT_MODE(testpkt.li_vn_mode));

	TEST_ASSERT_EQUAL(STRATUM_UNSPEC, PKT_TO_STRATUM(testpkt.stratum));
	TEST_ASSERT_EQUAL(8, testpkt.ppoll);

	TVTOTS(&xmt, &expected_xmt);
	NTOHL_FP(&testpkt.xmt, &actual_xmt);
	TEST_ASSERT_TRUE(LfpEquality(expected_xmt, actual_xmt));
}