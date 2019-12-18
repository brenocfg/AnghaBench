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
struct pt_query_decoder {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  ip; } ;
struct TYPE_8__ {int /*<<< orphan*/  ip; } ;
struct TYPE_7__ {int /*<<< orphan*/  ip; } ;
struct TYPE_6__ {int /*<<< orphan*/  ip; } ;
struct TYPE_10__ {TYPE_4__ async_vmcs; TYPE_3__ tsx; TYPE_2__ exec_mode; TYPE_1__ async_paging; } ;
struct pt_event {int status_update; int type; TYPE_5__ variant; } ;

/* Variables and functions */
 int pt_qry_event_ip (int /*<<< orphan*/ *,struct pt_event*,struct pt_query_decoder*) ; 
 int pt_qry_event_time (struct pt_event*,struct pt_query_decoder*) ; 
 int pte_internal ; 
#define  ptev_async_paging 133 
#define  ptev_async_vmcs 132 
#define  ptev_cbr 131 
#define  ptev_exec_mode 130 
#define  ptev_mnt 129 
#define  ptev_tsx 128 

__attribute__((used)) static int pt_qry_event_psbend(struct pt_event *ev,
			       struct pt_query_decoder *decoder)
{
	int errcode;

	if (!ev || !decoder)
		return -pte_internal;

	/* PSB+ events are status updates. */
	ev->status_update = 1;

	errcode = pt_qry_event_time(ev, decoder);
	if (errcode < 0)
		return errcode;

	switch (ev->type) {
	case ptev_async_paging:
		return pt_qry_event_ip(&ev->variant.async_paging.ip, ev,
				       decoder);

	case ptev_exec_mode:
		return pt_qry_event_ip(&ev->variant.exec_mode.ip, ev, decoder);

	case ptev_tsx:
		return pt_qry_event_ip(&ev->variant.tsx.ip, ev, decoder);

	case ptev_async_vmcs:
		return pt_qry_event_ip(&ev->variant.async_vmcs.ip, ev,
				       decoder);

	case ptev_cbr:
		return 0;

	case ptev_mnt:
		/* Maintenance packets may appear anywhere.  Do not mark them as
		 * status updates even if they appear in PSB+.
		 */
		ev->status_update = 0;
		return 0;

	default:
		break;
	}

	return -pte_internal;
}