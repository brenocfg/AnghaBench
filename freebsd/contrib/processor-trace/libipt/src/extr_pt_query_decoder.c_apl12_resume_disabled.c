#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct pt_query_decoder {unsigned int pos; int /*<<< orphan*/  config; int /*<<< orphan*/  tcal; int /*<<< orphan*/  time; } ;
struct pt_packet_decoder {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cyc; int /*<<< orphan*/  mtc; int /*<<< orphan*/  tma; int /*<<< orphan*/  cbr; int /*<<< orphan*/  tsc; } ;
struct pt_packet {int type; TYPE_1__ payload; } ;
typedef  int /*<<< orphan*/  packet ;

/* Variables and functions */
#define  ppt_cbr 135 
#define  ppt_cyc 134 
#define  ppt_mode 133 
#define  ppt_mtc 132 
#define  ppt_pip 131 
#define  ppt_tma 130 
#define  ppt_tsc 129 
#define  ppt_vmcs 128 
 int pt_pkt_get_offset (struct pt_packet_decoder*,scalar_t__*) ; 
 int pt_pkt_next (struct pt_packet_decoder*,struct pt_packet*,int) ; 
 int pt_pkt_sync_set (struct pt_packet_decoder*,scalar_t__) ; 
 int pt_qry_apply_cbr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pt_qry_apply_cyc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pt_qry_apply_mtc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pt_qry_apply_tma (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pt_qry_apply_tsc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pt_qry_event_ovf_disabled (struct pt_query_decoder*) ; 
 int pt_qry_get_offset (struct pt_query_decoder*,scalar_t__*) ; 
 int pte_eos ; 
 int pte_internal ; 

__attribute__((used)) static int apl12_resume_disabled(struct pt_query_decoder *decoder,
				 struct pt_packet_decoder *pkt,
				 unsigned int offset)
{
	uint64_t begin, end;
	int errcode;

	if (!decoder)
		return -pte_internal;

	errcode = pt_qry_get_offset(decoder, &begin);
	if (errcode < 0)
		return errcode;

	errcode = pt_pkt_sync_set(pkt, begin);
	if (errcode < 0)
		return errcode;

	end = begin + offset;
	for (;;) {
		struct pt_packet packet;
		uint64_t next;

		errcode = pt_pkt_next(pkt, &packet, sizeof(packet));
		if (errcode < 0) {
			/* Running out of packets is not an error. */
			if (errcode == -pte_eos)
				errcode = 0;

			return errcode;
		}

		/* The offset is the start of the next packet. */
		errcode = pt_pkt_get_offset(pkt, &next);
		if (errcode < 0)
			return errcode;

		/* We're done when we reach @offset.
		 *
		 * The current @packet will be the FUP after which we started
		 * our search.  We skip it.
		 *
		 * Check that we're not accidentally proceeding past @offset.
		 */
		if (end <= next) {
			if (end < next)
				return -pte_internal;

			break;
		}

		switch (packet.type) {
		default:
			/* Skip other packets. */
			break;

		case ppt_mode:
		case ppt_pip:
		case ppt_vmcs:
			/* We should not encounter those.
			 *
			 * We should not encounter a lot of packets but those
			 * are state-relevant; let's check them explicitly.
			 */
			return -pte_internal;

		case ppt_tsc:
			/* Keep track of time. */
			errcode = pt_qry_apply_tsc(&decoder->time,
						   &decoder->tcal,
						   &packet.payload.tsc,
						   &decoder->config);
			if (errcode < 0)
				return errcode;

			break;

		case ppt_cbr:
			/* Keep track of time. */
			errcode = pt_qry_apply_cbr(&decoder->time,
						   &decoder->tcal,
						   &packet.payload.cbr,
						   &decoder->config);
			if (errcode < 0)
				return errcode;

			break;

		case ppt_tma:
			/* Keep track of time. */
			errcode = pt_qry_apply_tma(&decoder->time,
						   &decoder->tcal,
						   &packet.payload.tma,
						   &decoder->config);
			if (errcode < 0)
				return errcode;

			break;

		case ppt_mtc:
			/* Keep track of time. */
			errcode = pt_qry_apply_mtc(&decoder->time,
						   &decoder->tcal,
						   &packet.payload.mtc,
						   &decoder->config);
			if (errcode < 0)
				return errcode;

			break;

		case ppt_cyc:
			/* Keep track of time. */
			errcode = pt_qry_apply_cyc(&decoder->time,
						   &decoder->tcal,
						   &packet.payload.cyc,
						   &decoder->config);
			if (errcode < 0)
				return errcode;

			break;
		}
	}

	decoder->pos += offset;

	return pt_qry_event_ovf_disabled(decoder);
}