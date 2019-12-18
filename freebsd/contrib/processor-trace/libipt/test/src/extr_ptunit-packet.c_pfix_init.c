#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ptunit_result {int dummy; } ;
struct TYPE_5__ {struct packet_fixture* context; int /*<<< orphan*/  callback; } ;
struct TYPE_6__ {int size; TYPE_1__ decode; struct TYPE_6__* end; struct TYPE_6__* begin; } ;
struct packet_fixture {scalar_t__ unknown; int /*<<< orphan*/  decoder; TYPE_2__ config; int /*<<< orphan*/  encoder; TYPE_2__* buffer; TYPE_2__* packet; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pfix_decode_unknown ; 
 int /*<<< orphan*/  pt_encoder_init (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  pt_pkt_decoder_init (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int pt_pkt_sync_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result pfix_init(struct packet_fixture *pfix)
{
	int errcode;

	memset(pfix->buffer, 0, sizeof(pfix->buffer));
	memset(pfix->packet, 0, sizeof(pfix->packet));
	memset(&pfix->config, 0, sizeof(pfix->config));
	pfix->config.size = sizeof(pfix->config);
	pfix->config.begin = pfix->buffer;
	pfix->config.end = pfix->buffer + sizeof(pfix->buffer);
	pfix->config.decode.callback = pfix_decode_unknown;
	pfix->config.decode.context = pfix;

	pt_encoder_init(&pfix->encoder, &pfix->config);
	pt_pkt_decoder_init(&pfix->decoder, &pfix->config);

	errcode = pt_pkt_sync_set(&pfix->decoder, 0x0ull);
	ptu_int_eq(errcode, 0);

	pfix->unknown = 0;

	return ptu_passed();
}