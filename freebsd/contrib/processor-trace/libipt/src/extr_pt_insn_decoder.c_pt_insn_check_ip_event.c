#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct pt_insn_ext {int dummy; } ;
struct TYPE_15__ {int /*<<< orphan*/  skd022; } ;
struct TYPE_16__ {TYPE_2__ errata; } ;
struct TYPE_17__ {TYPE_3__ config; } ;
struct TYPE_12__ {int /*<<< orphan*/  ip; } ;
struct TYPE_22__ {int /*<<< orphan*/  ip; } ;
struct TYPE_21__ {int /*<<< orphan*/  ip; } ;
struct TYPE_20__ {int /*<<< orphan*/  ip; } ;
struct TYPE_19__ {int /*<<< orphan*/  ip; } ;
struct TYPE_18__ {int /*<<< orphan*/  from; } ;
struct TYPE_14__ {int /*<<< orphan*/  at; } ;
struct TYPE_13__ {TYPE_10__ mwait; TYPE_9__ exstop; TYPE_8__ async_vmcs; TYPE_7__ async_paging; TYPE_6__ exec_mode; TYPE_5__ async_branch; TYPE_1__ async_disabled; } ;
struct pt_event {int type; TYPE_11__ variant; int /*<<< orphan*/  ip_suppressed; } ;
struct pt_insn_decoder {int /*<<< orphan*/  enabled; int /*<<< orphan*/  ip; TYPE_4__ query; struct pt_event event; } ;
struct pt_insn {int dummy; } ;

/* Variables and functions */
 int event_pending (struct pt_insn_decoder*) ; 
 int handle_erratum_skd022 (struct pt_insn_decoder*) ; 
 int pt_insn_postpone_tsx (struct pt_insn_decoder*,struct pt_insn const*,struct pt_insn_ext const*,struct pt_event*) ; 
 int pt_insn_status (struct pt_insn_decoder*,int /*<<< orphan*/ ) ; 
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

__attribute__((used)) static int pt_insn_check_ip_event(struct pt_insn_decoder *decoder,
				  const struct pt_insn *insn,
				  const struct pt_insn_ext *iext)
{
	struct pt_event *ev;
	int status;

	if (!decoder)
		return -pte_internal;

	status = event_pending(decoder);
	if (status <= 0) {
		if (status < 0)
			return status;

		return pt_insn_status(decoder, 0);
	}

	ev = &decoder->event;
	switch (ev->type) {
	case ptev_disabled:
		break;

	case ptev_enabled:
		return pt_insn_status(decoder, pts_event_pending);

	case ptev_async_disabled:
		if (ev->variant.async_disabled.at != decoder->ip)
			break;

		if (decoder->query.config.errata.skd022) {
			int errcode;

			errcode = handle_erratum_skd022(decoder);
			if (errcode != 0) {
				if (errcode < 0)
					return errcode;

				/* If the erratum applies, we postpone the
				 * modified event to the next call to
				 * pt_insn_next().
				 */
				break;
			}
		}

		return pt_insn_status(decoder, pts_event_pending);

	case ptev_tsx:
		status = pt_insn_postpone_tsx(decoder, insn, iext, ev);
		if (status != 0) {
			if (status < 0)
				return status;

			break;
		}

		return pt_insn_status(decoder, pts_event_pending);

	case ptev_async_branch:
		if (ev->variant.async_branch.from != decoder->ip)
			break;

		return pt_insn_status(decoder, pts_event_pending);

	case ptev_overflow:
		return pt_insn_status(decoder, pts_event_pending);

	case ptev_exec_mode:
		if (!ev->ip_suppressed &&
		    ev->variant.exec_mode.ip != decoder->ip)
			break;

		return pt_insn_status(decoder, pts_event_pending);

	case ptev_paging:
		if (decoder->enabled)
			break;

		return pt_insn_status(decoder, pts_event_pending);

	case ptev_async_paging:
		if (!ev->ip_suppressed &&
		    ev->variant.async_paging.ip != decoder->ip)
			break;

		return pt_insn_status(decoder, pts_event_pending);

	case ptev_vmcs:
		if (decoder->enabled)
			break;

		return pt_insn_status(decoder, pts_event_pending);

	case ptev_async_vmcs:
		if (!ev->ip_suppressed &&
		    ev->variant.async_vmcs.ip != decoder->ip)
			break;

		return pt_insn_status(decoder, pts_event_pending);

	case ptev_stop:
		return pt_insn_status(decoder, pts_event_pending);

	case ptev_exstop:
		if (!ev->ip_suppressed && decoder->enabled &&
		    decoder->ip != ev->variant.exstop.ip)
			break;

		return pt_insn_status(decoder, pts_event_pending);

	case ptev_mwait:
		if (!ev->ip_suppressed && decoder->enabled &&
		    decoder->ip != ev->variant.mwait.ip)
			break;

		return pt_insn_status(decoder, pts_event_pending);

	case ptev_pwre:
	case ptev_pwrx:
		return pt_insn_status(decoder, pts_event_pending);

	case ptev_ptwrite:
		/* Any event binding to the current PTWRITE instruction is
		 * handled in pt_insn_check_insn_event().
		 *
		 * Any subsequent ptwrite event binds to a different instruction
		 * and must wait until the next iteration - as long as tracing
		 * is enabled.
		 *
		 * When tracing is disabled, we forward all ptwrite events
		 * immediately to the user.
		 */
		if (decoder->enabled)
			break;

		return pt_insn_status(decoder, pts_event_pending);

	case ptev_tick:
	case ptev_cbr:
	case ptev_mnt:
		return pt_insn_status(decoder, pts_event_pending);
	}

	return pt_insn_status(decoder, 0);
}