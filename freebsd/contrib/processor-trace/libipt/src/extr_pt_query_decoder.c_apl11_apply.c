#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct pt_time_cal {int dummy; } ;
struct pt_time {int dummy; } ;
struct TYPE_8__ {scalar_t__ begin; } ;
struct pt_query_decoder {TYPE_2__ config; scalar_t__ pos; struct pt_time_cal tcal; struct pt_time time; } ;
struct pt_packet_decoder {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  cyc; int /*<<< orphan*/  mtc; int /*<<< orphan*/  tma; int /*<<< orphan*/  cbr; int /*<<< orphan*/  tsc; } ;
struct pt_packet {int type; TYPE_1__ payload; } ;
typedef  int /*<<< orphan*/  packet ;

/* Variables and functions */
#define  ppt_cbr 154 
#define  ppt_cyc 153 
#define  ppt_exstop 152 
#define  ppt_fup 151 
#define  ppt_invalid 150 
#define  ppt_mnt 149 
#define  ppt_mode 148 
#define  ppt_mtc 147 
#define  ppt_mwait 146 
#define  ppt_ovf 145 
#define  ppt_pad 144 
#define  ppt_pip 143 
#define  ppt_psb 142 
#define  ppt_psbend 141 
#define  ppt_ptw 140 
#define  ppt_pwre 139 
#define  ppt_pwrx 138 
#define  ppt_stop 137 
#define  ppt_tip 136 
#define  ppt_tip_pgd 135 
#define  ppt_tip_pge 134 
#define  ppt_tma 133 
#define  ppt_tnt_64 132 
#define  ppt_tnt_8 131 
#define  ppt_tsc 130 
#define  ppt_unknown 129 
#define  ppt_vmcs 128 
 int pt_pkt_get_offset (struct pt_packet_decoder*,scalar_t__*) ; 
 int pt_pkt_next (struct pt_packet_decoder*,struct pt_packet*,int) ; 
 int pt_qry_apply_cbr (struct pt_time*,struct pt_time_cal*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int pt_qry_apply_cyc (struct pt_time*,struct pt_time_cal*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int pt_qry_apply_mtc (struct pt_time*,struct pt_time_cal*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int pt_qry_apply_tma (struct pt_time*,struct pt_time_cal*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int pt_qry_apply_tsc (struct pt_time*,struct pt_time_cal*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int pt_qry_event_ovf_disabled (struct pt_query_decoder*) ; 
 int pte_bad_context ; 
 int pte_bad_opc ; 
 int pte_internal ; 

__attribute__((used)) static int apl11_apply(struct pt_query_decoder *decoder,
		       struct pt_packet_decoder *pkt)
{
	struct pt_time_cal tcal;
	struct pt_time time;

	if (!decoder)
		return -pte_internal;

	time = decoder->time;
	tcal = decoder->tcal;
	for (;;) {
		struct pt_packet packet;
		int errcode;

		errcode = pt_pkt_next(pkt, &packet, sizeof(packet));
		if (errcode < 0)
			return errcode;

		switch (packet.type) {
		case ppt_tip_pgd: {
			uint64_t offset;

			/* We found a TIP.PGD.  The erratum applies.
			 *
			 * Resume from here with tracing disabled.
			 */
			errcode = pt_pkt_get_offset(pkt, &offset);
			if (errcode < 0)
				return errcode;

			decoder->time = time;
			decoder->tcal = tcal;
			decoder->pos = decoder->config.begin + offset;

			return pt_qry_event_ovf_disabled(decoder);
		}

		case ppt_invalid:
			return -pte_bad_opc;

		case ppt_fup:
		case ppt_psb:
		case ppt_tip_pge:
		case ppt_stop:
		case ppt_ovf:
		case ppt_mode:
		case ppt_pip:
		case ppt_vmcs:
		case ppt_exstop:
		case ppt_mwait:
		case ppt_pwre:
		case ppt_pwrx:
		case ppt_ptw:
			/* The erratum does not apply. */
			return 1;

		case ppt_unknown:
		case ppt_pad:
		case ppt_mnt:
			/* Skip those packets. */
			break;

		case ppt_psbend:
		case ppt_tip:
		case ppt_tnt_8:
		case ppt_tnt_64:
			return -pte_bad_context;


		case ppt_tsc:
			/* Keep track of time. */
			errcode = pt_qry_apply_tsc(&time, &tcal,
						   &packet.payload.tsc,
						   &decoder->config);
			if (errcode < 0)
				return errcode;

			break;

		case ppt_cbr:
			/* Keep track of time. */
			errcode = pt_qry_apply_cbr(&time, &tcal,
						   &packet.payload.cbr,
						   &decoder->config);
			if (errcode < 0)
				return errcode;

			break;

		case ppt_tma:
			/* Keep track of time. */
			errcode = pt_qry_apply_tma(&time, &tcal,
						   &packet.payload.tma,
						   &decoder->config);
			if (errcode < 0)
				return errcode;

			break;

		case ppt_mtc:
			/* Keep track of time. */
			errcode = pt_qry_apply_mtc(&time, &tcal,
						   &packet.payload.mtc,
						   &decoder->config);
			if (errcode < 0)
				return errcode;

			break;

		case ppt_cyc:
			/* Keep track of time. */
			errcode = pt_qry_apply_cyc(&time, &tcal,
						   &packet.payload.cyc,
						   &decoder->config);
			if (errcode < 0)
				return errcode;

			break;
		}
	}
}