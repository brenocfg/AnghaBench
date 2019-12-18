#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned long l_ui; unsigned long l_uf; } ;
typedef  TYPE_1__ l_fp ;
struct TYPE_11__ {int /*<<< orphan*/  xmt; } ;
struct TYPE_10__ {int /*<<< orphan*/  org; } ;
struct TYPE_9__ {TYPE_4__ p; } ;
struct TYPE_8__ {TYPE_5__ p; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTHENTICATION ; 
 int /*<<< orphan*/  ENABLED_OPT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HTONL_FP (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LEN_PKT_NOMAC ; 
 int /*<<< orphan*/  MODE_SERVER ; 
 int /*<<< orphan*/  PACKET_UNUSEABLE ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_FALSE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_pkt (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,char*) ; 
 TYPE_3__ testpkt ; 
 int /*<<< orphan*/  testsock ; 
 TYPE_2__ testspkt ; 

void
test_RejectWrongResponseServerMode(void)
{
	TEST_ASSERT_FALSE(ENABLED_OPT(AUTHENTICATION));

	l_fp tmp;
	tmp.l_ui = 1000UL;
	tmp.l_uf = 0UL;
	HTONL_FP(&tmp, &testpkt.p.org);

	tmp.l_ui = 2000UL;
	tmp.l_uf = 0UL;
	HTONL_FP(&tmp, &testspkt.p.xmt);

	TEST_ASSERT_EQUAL(PACKET_UNUSEABLE,
			  process_pkt(&testpkt.p, &testsock, LEN_PKT_NOMAC,
				      MODE_SERVER, &testspkt.p, "UnitTest"));
}