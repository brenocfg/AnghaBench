#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct pt_query_decoder {int pos; int /*<<< orphan*/  evq; int /*<<< orphan*/  config; } ;
struct TYPE_9__ {int /*<<< orphan*/  abrt; int /*<<< orphan*/  intx; } ;
struct TYPE_10__ {TYPE_4__ tsx; int /*<<< orphan*/  exec; } ;
struct pt_packet_mode {int leaf; TYPE_5__ bits; } ;
struct TYPE_7__ {int /*<<< orphan*/  aborted; int /*<<< orphan*/  speculative; } ;
struct TYPE_6__ {int /*<<< orphan*/  mode; } ;
struct TYPE_8__ {TYPE_2__ tsx; TYPE_1__ exec_mode; } ;
struct pt_event {TYPE_3__ variant; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  evb_psbend ; 
 struct pt_event* pt_evq_enqueue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt_get_exec_mode (int /*<<< orphan*/ *) ; 
#define  pt_mol_exec 129 
#define  pt_mol_tsx 128 
 int pt_pkt_read_mode (struct pt_packet_mode*,int,int /*<<< orphan*/ *) ; 
 int pte_internal ; 
 int pte_nomem ; 
 int /*<<< orphan*/  ptev_exec_mode ; 
 int /*<<< orphan*/  ptev_tsx ; 

int pt_qry_header_mode(struct pt_query_decoder *decoder)
{
	struct pt_packet_mode packet;
	struct pt_event *event;
	int size;

	if (!decoder)
		return -pte_internal;

	size = pt_pkt_read_mode(&packet, decoder->pos, &decoder->config);
	if (size < 0)
		return size;

	/* Inside the header, events are reported at the end. */
	event = pt_evq_enqueue(&decoder->evq, evb_psbend);
	if (!event)
		return -pte_nomem;

	switch (packet.leaf) {
	case pt_mol_exec:
		event->type = ptev_exec_mode;
		event->variant.exec_mode.mode =
			pt_get_exec_mode(&packet.bits.exec);
		break;

	case pt_mol_tsx:
		event->type = ptev_tsx;
		event->variant.tsx.speculative = packet.bits.tsx.intx;
		event->variant.tsx.aborted = packet.bits.tsx.abrt;
		break;
	}

	decoder->pos += size;
	return 0;
}