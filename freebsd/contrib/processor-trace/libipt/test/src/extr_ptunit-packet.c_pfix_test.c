#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct ptunit_result {int dummy; } ;
struct packet_fixture {TYPE_1__* packet; int /*<<< orphan*/  decoder; int /*<<< orphan*/  encoder; } ;
struct TYPE_5__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int pt_enc_next (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int pt_pkt_next (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  ptu_int_gt (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_pkt_eq (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static struct ptunit_result pfix_test(struct packet_fixture *pfix)
{
	int size;

	size = pt_enc_next(&pfix->encoder, &pfix->packet[0]);
	ptu_int_gt(size, 0);

	pfix->packet[0].size = (uint8_t) size;

	size = pt_pkt_next(&pfix->decoder, &pfix->packet[1],
			   sizeof(pfix->packet[1]));
	ptu_int_gt(size, 0);

	return ptu_pkt_eq(&pfix->packet[0], &pfix->packet[1]);
}