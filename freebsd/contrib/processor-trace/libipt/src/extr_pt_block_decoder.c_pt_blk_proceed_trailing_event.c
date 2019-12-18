#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  ip; } ;
struct TYPE_13__ {int /*<<< orphan*/  ip; } ;
struct TYPE_24__ {int /*<<< orphan*/  ip; } ;
struct TYPE_23__ {int /*<<< orphan*/  ip; } ;
struct TYPE_22__ {int /*<<< orphan*/  ip; } ;
struct TYPE_21__ {int /*<<< orphan*/  from; } ;
struct TYPE_17__ {int /*<<< orphan*/  at; } ;
struct TYPE_16__ {int /*<<< orphan*/  ip; } ;
struct TYPE_15__ {TYPE_11__ mwait; TYPE_10__ exstop; TYPE_9__ exec_mode; TYPE_8__ async_vmcs; TYPE_7__ async_paging; TYPE_6__ async_branch; TYPE_2__ async_disabled; TYPE_1__ disabled; } ;
struct pt_event {int type; int /*<<< orphan*/  ip_suppressed; TYPE_12__ variant; } ;
struct TYPE_18__ {int /*<<< orphan*/  skd022; } ;
struct TYPE_19__ {TYPE_3__ errata; } ;
struct TYPE_20__ {TYPE_4__ config; } ;
struct pt_block_decoder {int bound_paging; int bound_vmcs; int bound_ptwrite; int /*<<< orphan*/  iext; int /*<<< orphan*/  insn; int /*<<< orphan*/  process_insn; int /*<<< orphan*/  enabled; int /*<<< orphan*/  ip; TYPE_5__ query; struct pt_event event; } ;
struct pt_block {int dummy; } ;

/* Variables and functions */
 int pt_blk_clear_postponed_insn (struct pt_block_decoder*) ; 
 int pt_blk_fetch_event (struct pt_block_decoder*) ; 
 int pt_blk_handle_erratum_skd022 (struct pt_block_decoder*,struct pt_event*) ; 
 int pt_blk_postpone_trailing_tsx (struct pt_block_decoder*,struct pt_block*,struct pt_event*) ; 
 int pt_blk_proceed_postponed_insn (struct pt_block_decoder*) ; 
 int pt_blk_set_disable_resume_ip (struct pt_block_decoder*,int /*<<< orphan*/ *) ; 
 int pt_blk_status (struct pt_block_decoder*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt_insn_binds_to_pip (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pt_insn_binds_to_vmcs (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pt_insn_changes_cr3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pt_insn_is_ptwrite (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pt_insn_next_ip (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
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

__attribute__((used)) static int pt_blk_proceed_trailing_event(struct pt_block_decoder *decoder,
					 struct pt_block *block)
{
	struct pt_event *ev;
	int status;

	if (!decoder)
		return -pte_internal;

	status = pt_blk_fetch_event(decoder);
	if (status <= 0) {
		if (status < 0)
			return status;

		status = pt_blk_proceed_postponed_insn(decoder);
		if (status < 0)
			return status;

		return pt_blk_status(decoder, 0);
	}

	ev = &decoder->event;
	switch (ev->type) {
	case ptev_disabled:
		/* Synchronous disable events are normally indicated on the
		 * event flow.
		 */
		if (!decoder->process_insn)
			break;

		/* A sync disable may bind to a CR3 changing instruction. */
		if (ev->ip_suppressed &&
		    pt_insn_changes_cr3(&decoder->insn, &decoder->iext))
			return pt_blk_status(decoder, pts_event_pending);

		/* Or it binds to the next branch that would require trace.
		 *
		 * Try to complete processing the current instruction by
		 * proceeding past it.  If that fails because it would require
		 * trace, we can apply the disabled event.
		 */
		status = pt_insn_next_ip(&decoder->ip, &decoder->insn,
					 &decoder->iext);
		if (status < 0) {
			if (status != -pte_bad_query)
				return status;

			status = pt_blk_set_disable_resume_ip(decoder,
							      &decoder->insn);
			if (status < 0)
				return status;

			return pt_blk_status(decoder, pts_event_pending);
		}

		/* We proceeded past the current instruction. */
		status = pt_blk_clear_postponed_insn(decoder);
		if (status < 0)
			return status;

		/* This might have brought us to the disable IP. */
		if (!ev->ip_suppressed &&
		    decoder->ip == ev->variant.disabled.ip)
			return pt_blk_status(decoder, pts_event_pending);

		break;

	case ptev_enabled:
		/* This event does not bind to an instruction. */
		status = pt_blk_proceed_postponed_insn(decoder);
		if (status < 0)
			return status;

		return pt_blk_status(decoder, pts_event_pending);

	case ptev_async_disabled:
		/* This event does not bind to an instruction. */
		status = pt_blk_proceed_postponed_insn(decoder);
		if (status < 0)
			return status;

		if (decoder->ip != ev->variant.async_disabled.at)
			break;

		if (decoder->query.config.errata.skd022) {
			status = pt_blk_handle_erratum_skd022(decoder, ev);
			if (status != 0) {
				if (status < 0)
					return status;

				/* If the erratum applies, the event is modified
				 * to a synchronous disable event that will be
				 * processed on the next pt_blk_proceed_event()
				 * call.  We're done.
				 */
				break;
			}
		}

		return pt_blk_status(decoder, pts_event_pending);

	case ptev_async_branch:
		/* This event does not bind to an instruction. */
		status = pt_blk_proceed_postponed_insn(decoder);
		if (status < 0)
			return status;

		if (decoder->ip != ev->variant.async_branch.from)
			break;

		return pt_blk_status(decoder, pts_event_pending);

	case ptev_paging:
		/* We apply the event immediately if we're not tracing. */
		if (!decoder->enabled)
			return pt_blk_status(decoder, pts_event_pending);

		/* Synchronous paging events are normally indicated on the event
		 * flow, unless they bind to the same instruction as a previous
		 * event.
		 *
		 * We bind at most one paging event to an instruction, though.
		 */
		if (!decoder->process_insn || decoder->bound_paging)
			break;

		/* We're done if we're not binding to the currently postponed
		 * instruction.  We will process the event on the normal event
		 * flow in the next iteration.
		 */
		if (!pt_insn_binds_to_pip(&decoder->insn, &decoder->iext))
			break;

		/* We bound a paging event.  Make sure we do not bind further
		 * paging events to this instruction.
		 */
		decoder->bound_paging = 1;

		return pt_blk_status(decoder, pts_event_pending);

	case ptev_async_paging:
		/* This event does not bind to an instruction. */
		status = pt_blk_proceed_postponed_insn(decoder);
		if (status < 0)
			return status;

		if (!ev->ip_suppressed &&
		    decoder->ip != ev->variant.async_paging.ip)
			break;

		return pt_blk_status(decoder, pts_event_pending);

	case ptev_vmcs:
		/* We apply the event immediately if we're not tracing. */
		if (!decoder->enabled)
			return pt_blk_status(decoder, pts_event_pending);

		/* Synchronous vmcs events are normally indicated on the event
		 * flow, unless they bind to the same instruction as a previous
		 * event.
		 *
		 * We bind at most one vmcs event to an instruction, though.
		 */
		if (!decoder->process_insn || decoder->bound_vmcs)
			break;

		/* We're done if we're not binding to the currently postponed
		 * instruction.  We will process the event on the normal event
		 * flow in the next iteration.
		 */
		if (!pt_insn_binds_to_vmcs(&decoder->insn, &decoder->iext))
			break;

		/* We bound a vmcs event.  Make sure we do not bind further vmcs
		 * events to this instruction.
		 */
		decoder->bound_vmcs = 1;

		return pt_blk_status(decoder, pts_event_pending);

	case ptev_async_vmcs:
		/* This event does not bind to an instruction. */
		status = pt_blk_proceed_postponed_insn(decoder);
		if (status < 0)
			return status;

		if (!ev->ip_suppressed &&
		    decoder->ip != ev->variant.async_vmcs.ip)
			break;

		return pt_blk_status(decoder, pts_event_pending);

	case ptev_overflow:
		/* This event does not bind to an instruction. */
		status = pt_blk_proceed_postponed_insn(decoder);
		if (status < 0)
			return status;

		return pt_blk_status(decoder, pts_event_pending);

	case ptev_exec_mode:
		/* This event does not bind to an instruction. */
		status = pt_blk_proceed_postponed_insn(decoder);
		if (status < 0)
			return status;

		if (!ev->ip_suppressed &&
		    decoder->ip != ev->variant.exec_mode.ip)
			break;

		return pt_blk_status(decoder, pts_event_pending);

	case ptev_tsx:
		/* This event does not bind to an instruction. */
		status = pt_blk_proceed_postponed_insn(decoder);
		if (status < 0)
			return status;

		status = pt_blk_postpone_trailing_tsx(decoder, block, ev);
		if (status != 0) {
			if (status < 0)
				return status;

			break;
		}

		return pt_blk_status(decoder, pts_event_pending);

	case ptev_stop:
		/* This event does not bind to an instruction. */
		status = pt_blk_proceed_postponed_insn(decoder);
		if (status < 0)
			return status;

		return pt_blk_status(decoder, pts_event_pending);

	case ptev_exstop:
		/* This event does not bind to an instruction. */
		status = pt_blk_proceed_postponed_insn(decoder);
		if (status < 0)
			return status;

		if (!ev->ip_suppressed && decoder->enabled &&
		    decoder->ip != ev->variant.exstop.ip)
			break;

		return pt_blk_status(decoder, pts_event_pending);

	case ptev_mwait:
		/* This event does not bind to an instruction. */
		status = pt_blk_proceed_postponed_insn(decoder);
		if (status < 0)
			return status;

		if (!ev->ip_suppressed && decoder->enabled &&
		    decoder->ip != ev->variant.mwait.ip)
			break;

		return pt_blk_status(decoder, pts_event_pending);

	case ptev_pwre:
	case ptev_pwrx:
		/* This event does not bind to an instruction. */
		status = pt_blk_proceed_postponed_insn(decoder);
		if (status < 0)
			return status;

		return pt_blk_status(decoder, pts_event_pending);

	case ptev_ptwrite:
		/* We apply the event immediately if we're not tracing. */
		if (!decoder->enabled)
			return pt_blk_status(decoder, pts_event_pending);

		/* Ptwrite events are normally indicated on the event flow,
		 * unless they bind to the same instruction as a previous event.
		 *
		 * We bind at most one ptwrite event to an instruction, though.
		 */
		if (!decoder->process_insn || decoder->bound_ptwrite)
			break;

		/* We're done if we're not binding to the currently postponed
		 * instruction.  We will process the event on the normal event
		 * flow in the next iteration.
		 */
		if (!ev->ip_suppressed ||
		    !pt_insn_is_ptwrite(&decoder->insn, &decoder->iext))
			break;

		/* We bound a ptwrite event.  Make sure we do not bind further
		 * ptwrite events to this instruction.
		 */
		decoder->bound_ptwrite = 1;

		return pt_blk_status(decoder, pts_event_pending);

	case ptev_tick:
	case ptev_cbr:
	case ptev_mnt:
		/* This event does not bind to an instruction. */
		status = pt_blk_proceed_postponed_insn(decoder);
		if (status < 0)
			return status;

		return pt_blk_status(decoder, pts_event_pending);
	}

	/* No further events.  Proceed past any postponed instruction. */
	status = pt_blk_proceed_postponed_insn(decoder);
	if (status < 0)
		return status;

	return pt_blk_status(decoder, 0);
}