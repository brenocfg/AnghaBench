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
struct pt_packet_pwre {scalar_t__ hw; int /*<<< orphan*/  sub_state; int /*<<< orphan*/  state; } ;
struct TYPE_3__ {int hw; int /*<<< orphan*/  sub_state; int /*<<< orphan*/  state; } ;
struct TYPE_4__ {TYPE_1__ pwre; } ;
struct pt_event {TYPE_2__ variant; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 struct pt_event* pt_evq_standalone (int /*<<< orphan*/ *) ; 
 int pt_pkt_read_pwre (struct pt_packet_pwre*,int,int /*<<< orphan*/ *) ; 
 int pte_internal ; 
 int /*<<< orphan*/  ptev_pwre ; 

int pt_qry_decode_pwre(struct pt_query_decoder *decoder)
{
	struct pt_packet_pwre packet;
	struct pt_event *event;
	int size;

	if (!decoder)
		return -pte_internal;

	size = pt_pkt_read_pwre(&packet, decoder->pos, &decoder->config);
	if (size < 0)
		return size;

	event = pt_evq_standalone(&decoder->evq);
	if (!event)
		return -pte_internal;

	event->type = ptev_pwre;
	event->variant.pwre.state = packet.state;
	event->variant.pwre.sub_state = packet.sub_state;

	if (packet.hw)
		event->variant.pwre.hw = 1;

	decoder->event = event;

	decoder->pos += size;
	return 0;
}