#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct pt_insn_ext {int dummy; } ;
struct pt_insn {int dummy; } ;
struct TYPE_17__ {int /*<<< orphan*/  ip; } ;
struct TYPE_16__ {int /*<<< orphan*/  ip; } ;
struct TYPE_15__ {int /*<<< orphan*/  ip; } ;
struct TYPE_14__ {int /*<<< orphan*/  from; } ;
struct TYPE_10__ {int /*<<< orphan*/  at; } ;
struct TYPE_18__ {TYPE_8__ mwait; TYPE_7__ exstop; TYPE_6__ tsx; TYPE_5__ async_branch; TYPE_1__ async_disabled; } ;
struct pt_event {int type; TYPE_9__ variant; int /*<<< orphan*/  ip_suppressed; } ;
struct TYPE_11__ {int /*<<< orphan*/  skd022; } ;
struct TYPE_12__ {TYPE_2__ errata; } ;
struct TYPE_13__ {TYPE_3__ config; } ;
struct pt_block_decoder {int bound_paging; int bound_vmcs; int bound_ptwrite; int /*<<< orphan*/  enabled; TYPE_4__ query; struct pt_event event; int /*<<< orphan*/  process_event; } ;
struct pt_block {int dummy; } ;

/* Variables and functions */
 int pt_blk_handle_erratum_skd022 (struct pt_block_decoder*,struct pt_event*) ; 
 int pt_blk_postpone_insn (struct pt_block_decoder*,struct pt_insn*,struct pt_insn_ext*) ; 
 int pt_blk_proceed_to_async_paging (struct pt_block_decoder*,struct pt_block*,struct pt_event*) ; 
 int pt_blk_proceed_to_async_vmcs (struct pt_block_decoder*,struct pt_block*,struct pt_event*) ; 
 int pt_blk_proceed_to_disabled (struct pt_block_decoder*,struct pt_block*,struct pt_insn*,struct pt_insn_ext*,struct pt_event*) ; 
 int pt_blk_proceed_to_exec_mode (struct pt_block_decoder*,struct pt_block*,struct pt_event*) ; 
 int pt_blk_proceed_to_insn (struct pt_block_decoder*,struct pt_block*,struct pt_insn*,struct pt_insn_ext*,int /*<<< orphan*/ ) ; 
 int pt_blk_proceed_to_ip (struct pt_block_decoder*,struct pt_block*,struct pt_insn*,struct pt_insn_ext*,int /*<<< orphan*/ ) ; 
 int pt_blk_proceed_to_ptwrite (struct pt_block_decoder*,struct pt_block*,struct pt_insn*,struct pt_insn_ext*,struct pt_event*) ; 
 int pt_blk_set_disable_resume_ip (struct pt_block_decoder*,struct pt_insn*) ; 
 int pt_blk_status (struct pt_block_decoder*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt_insn_binds_to_pip ; 
 int /*<<< orphan*/  pt_insn_binds_to_vmcs ; 
 int pte_bad_query ; 
 int pte_internal ; 
#define  ptev_async_branch 147 
#define  ptev_async_disabled 146 
#define  ptev_async_paging 145 
#define  ptev_async_vmcs 144 
#define  ptev_cbr 143 
#define  ptev_disabled 142 
#define  ptev_enabled 141 
#define  ptev_exec_mode 140 
#define  ptev_exstop 139 
#define  ptev_mnt 138 
#define  ptev_mwait 137 
#define  ptev_overflow 136 
#define  ptev_paging 135 
#define  ptev_ptwrite 134 
#define  ptev_pwre 133 
#define  ptev_pwrx 132 
#define  ptev_stop 131 
#define  ptev_tick 130 
#define  ptev_tsx 129 
#define  ptev_vmcs 128 
 int /*<<< orphan*/  pts_event_pending ; 

__attribute__((used)) static int pt_blk_proceed_event(struct pt_block_decoder *decoder,
				struct pt_block *block)
{
	struct pt_insn_ext iext;
	struct pt_insn insn;
	struct pt_event *ev;
	int status;

	if (!decoder || !decoder->process_event || !block)
		return -pte_internal;

	ev = &decoder->event;
	switch (ev->type) {
	case ptev_enabled:
		break;

	case ptev_disabled:
		status = pt_blk_proceed_to_disabled(decoder, block, &insn,
						    &iext, ev);
		if (status <= 0) {
			/* A synchronous disable event also binds to the next
			 * indirect or conditional branch, i.e. to any branch
			 * that would have required trace.
			 */
			if (status != -pte_bad_query)
				return status;

			status = pt_blk_set_disable_resume_ip(decoder, &insn);
			if (status < 0)
				return status;
		}

		break;

	case ptev_async_disabled:
		status = pt_blk_proceed_to_ip(decoder, block, &insn, &iext,
					      ev->variant.async_disabled.at);
		if (status <= 0)
			return status;

		if (decoder->query.config.errata.skd022) {
			status = pt_blk_handle_erratum_skd022(decoder, ev);
			if (status != 0) {
				if (status < 0)
					return status;

				/* If the erratum hits, we modify the event.
				 * Try again.
				 */
				return pt_blk_proceed_event(decoder, block);
			}
		}

		break;

	case ptev_async_branch:
		status = pt_blk_proceed_to_ip(decoder, block, &insn, &iext,
					      ev->variant.async_branch.from);
		if (status <= 0)
			return status;

		break;

	case ptev_paging:
		if (!decoder->enabled)
			break;

		status = pt_blk_proceed_to_insn(decoder, block, &insn, &iext,
						pt_insn_binds_to_pip);
		if (status <= 0)
			return status;

		/* We bound a paging event.  Make sure we do not bind further
		 * paging events to this instruction.
		 */
		decoder->bound_paging = 1;

		return pt_blk_postpone_insn(decoder, &insn, &iext);

	case ptev_async_paging:
		status = pt_blk_proceed_to_async_paging(decoder, block, ev);
		if (status <= 0)
			return status;

		break;

	case ptev_vmcs:
		if (!decoder->enabled)
			break;

		status = pt_blk_proceed_to_insn(decoder, block, &insn, &iext,
						pt_insn_binds_to_vmcs);
		if (status <= 0)
			return status;

		/* We bound a vmcs event.  Make sure we do not bind further vmcs
		 * events to this instruction.
		 */
		decoder->bound_vmcs = 1;

		return pt_blk_postpone_insn(decoder, &insn, &iext);

	case ptev_async_vmcs:
		status = pt_blk_proceed_to_async_vmcs(decoder, block, ev);
		if (status <= 0)
			return status;

		break;

	case ptev_overflow:
		break;

	case ptev_exec_mode:
		status = pt_blk_proceed_to_exec_mode(decoder, block, ev);
		if (status <= 0)
			return status;

		break;

	case ptev_tsx:
		if (ev->ip_suppressed)
			break;

		status = pt_blk_proceed_to_ip(decoder, block, &insn, &iext,
					      ev->variant.tsx.ip);
		if (status <= 0)
			return status;

		break;

	case ptev_stop:
		break;

	case ptev_exstop:
		if (!decoder->enabled || ev->ip_suppressed)
			break;

		status = pt_blk_proceed_to_ip(decoder, block, &insn, &iext,
					      ev->variant.exstop.ip);
		if (status <= 0)
			return status;

		break;

	case ptev_mwait:
		if (!decoder->enabled || ev->ip_suppressed)
			break;

		status = pt_blk_proceed_to_ip(decoder, block, &insn, &iext,
					      ev->variant.mwait.ip);
		if (status <= 0)
			return status;

		break;

	case ptev_pwre:
	case ptev_pwrx:
		break;

	case ptev_ptwrite:
		if (!decoder->enabled)
			break;

		status = pt_blk_proceed_to_ptwrite(decoder, block, &insn,
						   &iext, ev);
		if (status <= 0)
			return status;

		/* We bound a ptwrite event.  Make sure we do not bind further
		 * ptwrite events to this instruction.
		 */
		decoder->bound_ptwrite = 1;

		return pt_blk_postpone_insn(decoder, &insn, &iext);

	case ptev_tick:
	case ptev_cbr:
	case ptev_mnt:
		break;
	}

	return pt_blk_status(decoder, pts_event_pending);
}