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
struct pt_packet_vmcs {int /*<<< orphan*/  base; } ;
struct TYPE_3__ {int /*<<< orphan*/  base; } ;
struct TYPE_4__ {TYPE_1__ async_vmcs; } ;
struct pt_event {TYPE_2__ variant; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  evb_psbend ; 
 struct pt_event* pt_evq_enqueue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pt_pkt_read_vmcs (struct pt_packet_vmcs*,int,int /*<<< orphan*/ *) ; 
 int pte_internal ; 
 int pte_nomem ; 
 int /*<<< orphan*/  ptev_async_vmcs ; 

int pt_qry_header_vmcs(struct pt_query_decoder *decoder)
{
	struct pt_packet_vmcs packet;
	struct pt_event *event;
	int size;

	if (!decoder)
		return -pte_internal;

	size = pt_pkt_read_vmcs(&packet, decoder->pos, &decoder->config);
	if (size < 0)
		return size;

	event = pt_evq_enqueue(&decoder->evq, evb_psbend);
	if (!event)
		return -pte_nomem;

	event->type = ptev_async_vmcs;
	event->variant.async_vmcs.base = packet.base;

	decoder->pos += size;
	return 0;
}