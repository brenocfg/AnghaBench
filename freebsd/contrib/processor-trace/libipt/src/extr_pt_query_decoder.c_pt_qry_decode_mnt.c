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
struct pt_packet_mnt {int /*<<< orphan*/  payload; } ;
struct TYPE_3__ {int /*<<< orphan*/  payload; } ;
struct TYPE_4__ {TYPE_1__ mnt; } ;
struct pt_event {TYPE_2__ variant; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 struct pt_event* pt_evq_standalone (int /*<<< orphan*/ *) ; 
 int pt_pkt_read_mnt (struct pt_packet_mnt*,int,int /*<<< orphan*/ *) ; 
 int pt_qry_event_time (struct pt_event*,struct pt_query_decoder*) ; 
 int pte_internal ; 
 int /*<<< orphan*/  ptev_mnt ; 

int pt_qry_decode_mnt(struct pt_query_decoder *decoder)
{
	struct pt_packet_mnt packet;
	struct pt_event *event;
	int size, errcode;

	if (!decoder)
		return -pte_internal;

	size = pt_pkt_read_mnt(&packet, decoder->pos, &decoder->config);
	if (size < 0)
		return size;

	event = pt_evq_standalone(&decoder->evq);
	if (!event)
		return -pte_internal;

	event->type = ptev_mnt;
	event->variant.mnt.payload = packet.payload;

	decoder->event = event;

	errcode = pt_qry_event_time(event, decoder);
	if (errcode < 0)
		return errcode;

	decoder->pos += size;

	return 0;
}