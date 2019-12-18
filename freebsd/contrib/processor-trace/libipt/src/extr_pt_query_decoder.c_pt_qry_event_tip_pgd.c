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
typedef  int /*<<< orphan*/  uint64_t ;
struct pt_query_decoder {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  ip; int /*<<< orphan*/  at; } ;
struct TYPE_4__ {int /*<<< orphan*/  from; } ;
struct TYPE_5__ {TYPE_3__ async_disabled; TYPE_1__ async_branch; } ;
struct pt_event {int type; int ip_suppressed; TYPE_2__ variant; } ;

/* Variables and functions */
 int pt_qry_event_ip (int /*<<< orphan*/ *,struct pt_event*,struct pt_query_decoder const*) ; 
 int pte_bad_context ; 
 int pte_internal ; 
#define  ptev_async_branch 131 
 int ptev_async_disabled ; 
#define  ptev_async_paging 130 
#define  ptev_async_vmcs 129 
#define  ptev_exec_mode 128 

__attribute__((used)) static int pt_qry_event_tip_pgd(struct pt_event *ev,
				const struct pt_query_decoder *decoder)
{
	if (!ev)
		return -pte_internal;

	switch (ev->type) {
	case ptev_async_branch: {
		uint64_t at;

		/* Turn the async branch into an async disable. */
		at = ev->variant.async_branch.from;

		ev->type = ptev_async_disabled;
		ev->variant.async_disabled.at = at;

		return pt_qry_event_ip(&ev->variant.async_disabled.ip, ev,
				       decoder);
	}

	case ptev_async_paging:
	case ptev_async_vmcs:
	case ptev_exec_mode:
		/* These events are ordered after the async disable event.  It
		 * is not quite clear what IP to give them.
		 *
		 * If we give them the async disable's source IP, we'd make an
		 * error if the IP is updated when applying the async disable
		 * event.
		 *
		 * If we give them the async disable's destination IP, we'd make
		 * an error if the IP is not updated when applying the async
		 * disable event.  That's what our decoders do since tracing is
		 * likely to resume from there.
		 *
		 * In all cases, tracing will be disabled when those events are
		 * applied, so we may as well suppress the IP.
		 */
		ev->ip_suppressed = 1;

		return 0;

	default:
		break;
	}

	return -pte_bad_context;
}