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
struct ptunit_result {int dummy; } ;
struct packet_fixture {int unknown; TYPE_3__* packet; struct packet_fixture* buffer; int /*<<< orphan*/  decoder; } ;
struct TYPE_4__ {int /*<<< orphan*/  priv; int /*<<< orphan*/  packet; } ;
struct TYPE_5__ {TYPE_1__ unknown; } ;
struct TYPE_6__ {int type; TYPE_2__ payload; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int ppt_unknown ; 
 struct packet_fixture pt_opc_bad ; 
 int pt_pkt_next (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_ptr_eq (int /*<<< orphan*/ ,struct packet_fixture*) ; 
 int /*<<< orphan*/  ptu_uint_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ptunit_result unknown(struct packet_fixture *pfix, int exp)
{
	int size;

	pfix->buffer[0] = pt_opc_bad;
	pfix->unknown = exp;

	size = pt_pkt_next(&pfix->decoder, &pfix->packet[1],
			   sizeof(pfix->packet[1]));
	ptu_int_eq(size, pfix->unknown);

	if (size >= 0) {
		ptu_int_eq(pfix->packet[1].type, ppt_unknown);
		ptu_uint_eq(pfix->packet[1].size, (uint8_t) size);
		ptu_ptr_eq(pfix->packet[1].payload.unknown.packet,
			   pfix->buffer);
		ptu_ptr_eq(pfix->packet[1].payload.unknown.priv, pfix);
	}

	return ptu_passed();
}