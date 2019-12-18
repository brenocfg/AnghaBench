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
struct pt_query_decoder {int pos; struct pt_event* event; int /*<<< orphan*/  evq; int /*<<< orphan*/  config; } ;
struct pt_packet_exstop {scalar_t__ ip; } ;
struct TYPE_3__ {unsigned long long ip; } ;
struct TYPE_4__ {TYPE_1__ exstop; } ;
struct pt_event {int ip_suppressed; TYPE_2__ variant; void* type; } ;

/* Variables and functions */
 int /*<<< orphan*/  evb_fup ; 
 struct pt_event* pt_evq_enqueue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct pt_event* pt_evq_standalone (int /*<<< orphan*/ *) ; 
 int pt_pkt_read_exstop (struct pt_packet_exstop*,int,int /*<<< orphan*/ *) ; 
 int pte_internal ; 
 void* ptev_exstop ; 

int pt_qry_decode_exstop(struct pt_query_decoder *decoder)
{
	struct pt_packet_exstop packet;
	struct pt_event *event;
	int size;

	if (!decoder)
		return -pte_internal;

	size = pt_pkt_read_exstop(&packet, decoder->pos, &decoder->config);
	if (size < 0)
		return size;

	if (packet.ip) {
		event = pt_evq_enqueue(&decoder->evq, evb_fup);
		if (!event)
			return -pte_internal;

		event->type = ptev_exstop;
	} else {
		event = pt_evq_standalone(&decoder->evq);
		if (!event)
			return -pte_internal;

		event->type = ptev_exstop;

		event->ip_suppressed = 1;
		event->variant.exstop.ip = 0ull;

		decoder->event = event;
	}

	decoder->pos += size;
	return 0;
}