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
struct pt_query_decoder {int pos; int /*<<< orphan*/  evq; int /*<<< orphan*/  config; } ;
struct pt_packet_mwait {int /*<<< orphan*/  ext; int /*<<< orphan*/  hints; } ;
struct TYPE_3__ {int /*<<< orphan*/  ext; int /*<<< orphan*/  hints; } ;
struct TYPE_4__ {TYPE_1__ mwait; } ;
struct pt_event {TYPE_2__ variant; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  evb_fup ; 
 struct pt_event* pt_evq_enqueue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pt_pkt_read_mwait (struct pt_packet_mwait*,int,int /*<<< orphan*/ *) ; 
 int pte_internal ; 
 int /*<<< orphan*/  ptev_mwait ; 

int pt_qry_decode_mwait(struct pt_query_decoder *decoder)
{
	struct pt_packet_mwait packet;
	struct pt_event *event;
	int size;

	if (!decoder)
		return -pte_internal;

	size = pt_pkt_read_mwait(&packet, decoder->pos, &decoder->config);
	if (size < 0)
		return size;

	event = pt_evq_enqueue(&decoder->evq, evb_fup);
	if (!event)
		return -pte_internal;

	event->type = ptev_mwait;
	event->variant.mwait.hints = packet.hints;
	event->variant.mwait.ext = packet.ext;

	decoder->pos += size;
	return 0;
}