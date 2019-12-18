#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pt_insn_ext {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  config; } ;
struct TYPE_5__ {unsigned long long ip; } ;
struct TYPE_6__ {TYPE_2__ ptwrite; } ;
struct pt_event {int type; TYPE_3__ variant; int /*<<< orphan*/  ip_suppressed; } ;
struct pt_insn_decoder {unsigned long long ip; int bound_paging; int bound_vmcs; int bound_ptwrite; TYPE_1__ query; struct pt_event event; } ;
struct pt_insn {unsigned long long ip; unsigned long long size; int /*<<< orphan*/  iclass; } ;

/* Variables and functions */
 int event_pending (struct pt_insn_decoder*) ; 
 int pt_insn_at_disabled_event (struct pt_event*,struct pt_insn const*,struct pt_insn_ext const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pt_insn_binds_to_pip (struct pt_insn const*,struct pt_insn_ext const*) ; 
 int /*<<< orphan*/  pt_insn_binds_to_vmcs (struct pt_insn const*,struct pt_insn_ext const*) ; 
 int /*<<< orphan*/  pt_insn_is_ptwrite (struct pt_insn const*,struct pt_insn_ext const*) ; 
 int pt_insn_next_ip (unsigned long long*,struct pt_insn const*,struct pt_insn_ext const*) ; 
 int pt_insn_postpone (struct pt_insn_decoder*,struct pt_insn const*,struct pt_insn_ext const*) ; 
 int pt_insn_status (struct pt_insn_decoder*,int /*<<< orphan*/ ) ; 
 int pte_bad_query ; 
 int pte_internal ; 
#define  ptev_async_branch 149 
#define  ptev_async_disabled 148 
#define  ptev_async_paging 147 
#define  ptev_async_vmcs 146 
#define  ptev_cbr 145 
#define  ptev_disabled 144 
#define  ptev_enabled 143 
#define  ptev_exec_mode 142 
#define  ptev_exstop 141 
#define  ptev_mnt 140 
#define  ptev_mwait 139 
#define  ptev_overflow 138 
#define  ptev_paging 137 
#define  ptev_ptwrite 136 
#define  ptev_pwre 135 
#define  ptev_pwrx 134 
#define  ptev_stop 133 
#define  ptev_tick 132 
#define  ptev_tsx 131 
#define  ptev_vmcs 130 
#define  ptic_call 129 
#define  ptic_far_call 128 
 int /*<<< orphan*/  pts_event_pending ; 

__attribute__((used)) static int pt_insn_check_insn_event(struct pt_insn_decoder *decoder,
				    const struct pt_insn *insn,
				    const struct pt_insn_ext *iext)
{
	struct pt_event *ev;
	int status;

	if (!decoder)
		return -pte_internal;

	status = event_pending(decoder);
	if (status <= 0)
		return status;

	ev = &decoder->event;
	switch (ev->type) {
	case ptev_enabled:
	case ptev_overflow:
	case ptev_async_paging:
	case ptev_async_vmcs:
	case ptev_async_disabled:
	case ptev_async_branch:
	case ptev_exec_mode:
	case ptev_tsx:
	case ptev_stop:
	case ptev_exstop:
	case ptev_mwait:
	case ptev_pwre:
	case ptev_pwrx:
	case ptev_tick:
	case ptev_cbr:
	case ptev_mnt:
		/* We're only interested in events that bind to instructions. */
		return 0;

	case ptev_disabled:
		status = pt_insn_at_disabled_event(ev, insn, iext,
						   &decoder->query.config);
		if (status <= 0)
			return status;

		/* We're at a synchronous disable event location.
		 *
		 * Let's determine the IP at which we expect tracing to resume.
		 */
		status = pt_insn_next_ip(&decoder->ip, insn, iext);
		if (status < 0) {
			/* We don't know the IP on error. */
			decoder->ip = 0ull;

			/* For indirect calls, assume that we return to the next
			 * instruction.
			 *
			 * We only check the instruction class, not the
			 * is_direct property, since direct calls would have
			 * been handled by pt_insn_nex_ip() or would have
			 * provoked a different error.
			 */
			if (status != -pte_bad_query)
				return status;

			switch (insn->iclass) {
			case ptic_call:
			case ptic_far_call:
				decoder->ip = insn->ip + insn->size;
				break;

			default:
				break;
			}
		}

		break;

	case ptev_paging:
		/* We bind at most one paging event to an instruction. */
		if (decoder->bound_paging)
			return 0;

		if (!pt_insn_binds_to_pip(insn, iext))
			return 0;

		/* We bound a paging event.  Make sure we do not bind further
		 * paging events to this instruction.
		 */
		decoder->bound_paging = 1;

		return pt_insn_postpone(decoder, insn, iext);

	case ptev_vmcs:
		/* We bind at most one vmcs event to an instruction. */
		if (decoder->bound_vmcs)
			return 0;

		if (!pt_insn_binds_to_vmcs(insn, iext))
			return 0;

		/* We bound a vmcs event.  Make sure we do not bind further vmcs
		 * events to this instruction.
		 */
		decoder->bound_vmcs = 1;

		return pt_insn_postpone(decoder, insn, iext);

	case ptev_ptwrite:
		/* We bind at most one ptwrite event to an instruction. */
		if (decoder->bound_ptwrite)
			return 0;

		if (ev->ip_suppressed) {
			if (!pt_insn_is_ptwrite(insn, iext))
				return 0;

			/* Fill in the event IP.  Our users will need them to
			 * make sense of the PTWRITE payload.
			 */
			ev->variant.ptwrite.ip = decoder->ip;
			ev->ip_suppressed = 0;
		} else {
			/* The ptwrite event contains the IP of the ptwrite
			 * instruction (CLIP) unlike most events that contain
			 * the IP of the first instruction that did not complete
			 * (NLIP).
			 *
			 * It's easier to handle this case here, as well.
			 */
			if (decoder->ip != ev->variant.ptwrite.ip)
				return 0;
		}

		/* We bound a ptwrite event.  Make sure we do not bind further
		 * ptwrite events to this instruction.
		 */
		decoder->bound_ptwrite = 1;

		return pt_insn_postpone(decoder, insn, iext);
	}

	return pt_insn_status(decoder, pts_event_pending);
}