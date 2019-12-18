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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/ * exten; } ;
struct TYPE_5__ {TYPE_3__ p; } ;
struct TYPE_4__ {int /*<<< orphan*/  p; } ;

/* Variables and functions */
 int LEN_PKT_NOMAC ; 
 int /*<<< orphan*/  MODE_SERVER ; 
 int /*<<< orphan*/  PACKET_UNUSEABLE ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  process_pkt (TYPE_3__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 TYPE_2__ testpkt ; 
 int /*<<< orphan*/  testsock ; 
 TYPE_1__ testspkt ; 

void
test_TooShortExtensionFieldLength(void)
{
	/* [Bug 2998] We have to get around the formal specification of
	 * the extension field if AUTOKEY is undefined. (At least CLANG
	 * issues a warning in this case. It's just a warning, but
	 * still...
	 */
	uint32_t * pe = testpkt.p.exten + 7;
	
	/* The lower 16-bits are the length of the extension field.
	 * This lengths must be multiples of 4 bytes, which gives
	 * a minimum of 4 byte extension field length.
	 */
	*pe = htonl(3); /* 3 bytes is too short. */

	/* We send in a pkt_len of header size + 4 byte extension
	 * header + 24 byte MAC, this prevents the length error to
	 * be caught at an earlier stage
	 */
	int pkt_len = LEN_PKT_NOMAC + 4 + 24;

	TEST_ASSERT_EQUAL(PACKET_UNUSEABLE,
			  process_pkt(&testpkt.p, &testsock, pkt_len,
				      MODE_SERVER, &testspkt.p, "UnitTest"));
}