#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct pt_query_decoder {int pos; struct pt_event* event; int /*<<< orphan*/  evq; int /*<<< orphan*/  config; } ;
struct pt_packet_ptw {int /*<<< orphan*/  payload; scalar_t__ ip; int /*<<< orphan*/  plc; } ;
struct TYPE_3__ {int /*<<< orphan*/  payload; int /*<<< orphan*/  size; } ;
struct TYPE_4__ {TYPE_1__ ptwrite; } ;
struct pt_event {int ip_suppressed; TYPE_2__ variant; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  evb_fup ; 
 struct pt_event* pt_evq_enqueue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct pt_event* pt_evq_standalone (int /*<<< orphan*/ *) ; 
 int pt_pkt_read_ptw (struct pt_packet_ptw*,int,int /*<<< orphan*/ *) ; 
 int pt_ptw_size (int /*<<< orphan*/ ) ; 
 int pte_internal ; 
 int /*<<< orphan*/  ptev_ptwrite ; 

int pt_qry_decode_ptw(struct pt_query_decoder *decoder)
{
	struct pt_packet_ptw packet;
	struct pt_event *event;
	int size, pls;

	if (!decoder)
		return -pte_internal;

	size = pt_pkt_read_ptw(&packet, decoder->pos, &decoder->config);
	if (size < 0)
		return size;

	pls = pt_ptw_size(packet.plc);
	if (pls < 0)
		return pls;

	if (packet.ip) {
		event = pt_evq_enqueue(&decoder->evq, evb_fup);
		if (!event)
			return -pte_internal;
	} else {
		event = pt_evq_standalone(&decoder->evq);
		if (!event)
			return -pte_internal;

		event->ip_suppressed = 1;

		decoder->event = event;
	}

	event->type = ptev_ptwrite;
	event->variant.ptwrite.size = (uint8_t) pls;
	event->variant.ptwrite.payload = packet.payload;

	decoder->pos += size;
	return 0;
}