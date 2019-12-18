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
struct ptunit_result {int dummy; } ;
struct packet_fixture {TYPE_3__* packet; int /*<<< orphan*/  encoder; } ;
struct TYPE_4__ {int ctc; int fc; } ;
struct TYPE_5__ {TYPE_1__ tma; } ;
struct TYPE_6__ {TYPE_2__ payload; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ppt_tma ; 
 int pt_enc_next (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  pte_bad_packet ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result tma_bad(struct packet_fixture *pfix)
{
	int errcode;

	pfix->packet[0].type = ppt_tma;
	pfix->packet[0].payload.tma.ctc = 0x42;
	pfix->packet[0].payload.tma.fc = 0x200;

	errcode = pt_enc_next(&pfix->encoder, &pfix->packet[0]);
	ptu_int_eq(errcode, -pte_bad_packet);

	return ptu_passed();
}