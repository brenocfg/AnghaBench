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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
struct ptunit_result {int dummy; } ;
struct packet_fixture {TYPE_3__* packet; } ;
typedef  int /*<<< orphan*/  mask ;
struct TYPE_4__ {int payload; int ip; int /*<<< orphan*/  plc; } ;
struct TYPE_5__ {TYPE_1__ ptw; } ;
struct TYPE_6__ {TYPE_2__ payload; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  pfix_test ; 
 int /*<<< orphan*/  ppt_ptw ; 
 int pt_ptw_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptu_int_gt (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_test (int /*<<< orphan*/ ,struct packet_fixture*) ; 
 int /*<<< orphan*/  ptu_uint_le (size_t,int) ; 

__attribute__((used)) static struct ptunit_result ptw(struct packet_fixture *pfix, uint8_t plc,
				int ip)
{
	uint64_t pl, mask;
	int size;

	size = pt_ptw_size(plc);
	ptu_int_gt(size, 0);

	pl = 0x1234567890abcdefull;

	ptu_uint_le((size_t) size, sizeof(mask));
	mask = ~0ull >> ((sizeof(mask) - (size_t) size) * 8);

	pfix->packet[0].type = ppt_ptw;
	pfix->packet[0].payload.ptw.payload = pl & mask;
	pfix->packet[0].payload.ptw.plc = plc;
	pfix->packet[0].payload.ptw.ip = ip ? 1 : 0;

	ptu_test(pfix_test, pfix);

	return ptu_passed();
}