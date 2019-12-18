#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  ip; } ;
struct TYPE_19__ {int /*<<< orphan*/  ip; } ;
struct TYPE_18__ {int /*<<< orphan*/  ip; } ;
struct TYPE_17__ {int /*<<< orphan*/  ip; } ;
struct TYPE_16__ {int /*<<< orphan*/  ip; } ;
struct TYPE_15__ {int /*<<< orphan*/  ip; } ;
struct TYPE_14__ {int /*<<< orphan*/  from; } ;
struct TYPE_13__ {int /*<<< orphan*/  at; } ;
struct TYPE_12__ {int resumed; int /*<<< orphan*/  ip; } ;
struct TYPE_11__ {TYPE_9__ mwait; TYPE_8__ exstop; TYPE_7__ tsx; TYPE_6__ exec_mode; TYPE_5__ async_vmcs; TYPE_4__ async_paging; TYPE_3__ async_branch; TYPE_2__ async_disabled; TYPE_1__ enabled; } ;
struct pt_event {int type; TYPE_10__ variant; int /*<<< orphan*/  ip_suppressed; } ;
struct pt_block_decoder {int /*<<< orphan*/  process_event; int /*<<< orphan*/  ip; int /*<<< orphan*/  enabled; struct pt_event event; } ;

/* Variables and functions */
 int /*<<< orphan*/  fallthrough ; 
 int /*<<< orphan*/  memcpy (struct pt_event*,struct pt_event*,size_t) ; 
 int pt_blk_proceed_trailing_event (struct pt_block_decoder*,int /*<<< orphan*/ *) ; 
 int pt_blk_process_async_branch (struct pt_block_decoder*,struct pt_event*) ; 
 int pt_blk_process_disabled (struct pt_block_decoder*,struct pt_event*) ; 
 int pt_blk_process_enabled (struct pt_block_decoder*,struct pt_event*) ; 
 int pt_blk_process_exec_mode (struct pt_block_decoder*,struct pt_event*) ; 
 int pt_blk_process_overflow (struct pt_block_decoder*,struct pt_event*) ; 
 int pt_blk_process_paging (struct pt_block_decoder*,struct pt_event*) ; 
 int pt_blk_process_stop (struct pt_block_decoder*,struct pt_event*) ; 
 int pt_blk_process_tsx (struct pt_block_decoder*,struct pt_event*) ; 
 int pt_blk_process_vmcs (struct pt_block_decoder*,struct pt_event*) ; 
 int pte_bad_query ; 
 int pte_invalid ; 
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

int pt_blk_event(struct pt_block_decoder *decoder, struct pt_event *uevent,
		 size_t size)
{
	struct pt_event *ev;
	int status;

	if (!decoder || !uevent)
		return -pte_invalid;

	/* We must currently process an event. */
	if (!decoder->process_event)
		return -pte_bad_query;

	ev = &decoder->event;
	switch (ev->type) {
	case ptev_enabled:
		/* Indicate that tracing resumes from the IP at which tracing
		 * had been disabled before (with some special treatment for
		 * calls).
		 */
		if (ev->variant.enabled.ip == decoder->ip)
			ev->variant.enabled.resumed = 1;

		status = pt_blk_process_enabled(decoder, ev);
		if (status < 0)
			return status;

		break;

	case ptev_async_disabled:
		if (decoder->ip != ev->variant.async_disabled.at)
			return -pte_bad_query;

		fallthrough;
	case ptev_disabled:

		status = pt_blk_process_disabled(decoder, ev);
		if (status < 0)
			return status;

		break;

	case ptev_async_branch:
		if (decoder->ip != ev->variant.async_branch.from)
			return -pte_bad_query;

		status = pt_blk_process_async_branch(decoder, ev);
		if (status < 0)
			return status;

		break;

	case ptev_async_paging:
		if (!ev->ip_suppressed &&
		    decoder->ip != ev->variant.async_paging.ip)
			return -pte_bad_query;

		fallthrough;
	case ptev_paging:
		status = pt_blk_process_paging(decoder, ev);
		if (status < 0)
			return status;

		break;

	case ptev_async_vmcs:
		if (!ev->ip_suppressed &&
		    decoder->ip != ev->variant.async_vmcs.ip)
			return -pte_bad_query;

		fallthrough;
	case ptev_vmcs:
		status = pt_blk_process_vmcs(decoder, ev);
		if (status < 0)
			return status;

		break;

	case ptev_overflow:
		status = pt_blk_process_overflow(decoder, ev);
		if (status < 0)
			return status;

		break;

	case ptev_exec_mode:
		if (!ev->ip_suppressed &&
		    decoder->ip != ev->variant.exec_mode.ip)
			return -pte_bad_query;

		status = pt_blk_process_exec_mode(decoder, ev);
		if (status < 0)
			return status;

		break;

	case ptev_tsx:
		if (!ev->ip_suppressed && decoder->ip != ev->variant.tsx.ip)
			return -pte_bad_query;

		status = pt_blk_process_tsx(decoder, ev);
		if (status < 0)
			return status;

		break;

	case ptev_stop:
		status = pt_blk_process_stop(decoder, ev);
		if (status < 0)
			return status;

		break;

	case ptev_exstop:
		if (!ev->ip_suppressed && decoder->enabled &&
		    decoder->ip != ev->variant.exstop.ip)
			return -pte_bad_query;

		decoder->process_event = 0;
		break;

	case ptev_mwait:
		if (!ev->ip_suppressed && decoder->enabled &&
		    decoder->ip != ev->variant.mwait.ip)
			return -pte_bad_query;

		decoder->process_event = 0;
		break;

	case ptev_pwre:
	case ptev_pwrx:
	case ptev_ptwrite:
	case ptev_tick:
	case ptev_cbr:
	case ptev_mnt:
		decoder->process_event = 0;
		break;
	}

	/* Copy the event to the user.  Make sure we're not writing beyond the
	 * memory provided by the user.
	 *
	 * We might truncate details of an event but only for those events the
	 * user can't know about, anyway.
	 */
	if (sizeof(*ev) < size)
		size = sizeof(*ev);

	memcpy(uevent, ev, size);

	/* Indicate further events. */
	return pt_blk_proceed_trailing_event(decoder, NULL);
}