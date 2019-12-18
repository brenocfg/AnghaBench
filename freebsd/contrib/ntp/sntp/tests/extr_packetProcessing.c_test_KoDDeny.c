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
struct TYPE_6__ {int /*<<< orphan*/  refid; int /*<<< orphan*/  stratum; } ;
struct TYPE_5__ {TYPE_3__ p; } ;
struct TYPE_4__ {int /*<<< orphan*/  p; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTHENTICATION ; 
 int /*<<< orphan*/  ENABLED_OPT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KOD_DEMOBILIZE ; 
 int /*<<< orphan*/  LEN_PKT_NOMAC ; 
 int /*<<< orphan*/  MODE_SERVER ; 
 int /*<<< orphan*/  STRATUM_PKT_UNSPEC ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_FALSE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  process_pkt (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 TYPE_2__ testpkt ; 
 int /*<<< orphan*/  testsock ; 
 TYPE_1__ testspkt ; 

void
test_KoDDeny(void)
{
	TEST_ASSERT_FALSE(ENABLED_OPT(AUTHENTICATION));

	testpkt.p.stratum = STRATUM_PKT_UNSPEC;
	memcpy(&testpkt.p.refid, "DENY", 4);

	TEST_ASSERT_EQUAL(KOD_DEMOBILIZE,
			  process_pkt(&testpkt.p, &testsock, LEN_PKT_NOMAC,
				      MODE_SERVER, &testspkt.p, "UnitTest"));
}