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
struct pt_query_decoder {int consume_packet; } ;
struct TYPE_7__ {int /*<<< orphan*/  ip; } ;
struct TYPE_6__ {int /*<<< orphan*/  ip; } ;
struct TYPE_10__ {int /*<<< orphan*/  ip; } ;
struct TYPE_8__ {int /*<<< orphan*/  to; } ;
struct TYPE_9__ {TYPE_2__ exec_mode; TYPE_1__ async_vmcs; TYPE_5__ async_paging; TYPE_3__ async_branch; } ;
struct pt_event {int type; TYPE_4__ variant; } ;

/* Variables and functions */
 int pt_qry_event_ip (int /*<<< orphan*/ *,struct pt_event*,struct pt_query_decoder*) ; 
 int pte_bad_context ; 
 int pte_internal ; 
#define  ptev_async_branch 131 
#define  ptev_async_paging 130 
#define  ptev_async_vmcs 129 
#define  ptev_exec_mode 128 

__attribute__((used)) static int pt_qry_event_tip(struct pt_event *ev,
			    struct pt_query_decoder *decoder)
{
	if (!ev || !decoder)
		return -pte_internal;

	switch (ev->type) {
	case ptev_async_branch:
		decoder->consume_packet = 1;

		return pt_qry_event_ip(&ev->variant.async_branch.to, ev,
				       decoder);

	case ptev_async_paging:
		return pt_qry_event_ip(&ev->variant.async_paging.ip, ev,
				       decoder);

	case ptev_async_vmcs:
		return pt_qry_event_ip(&ev->variant.async_vmcs.ip, ev,
				       decoder);

	case ptev_exec_mode:
		return pt_qry_event_ip(&ev->variant.exec_mode.ip, ev,
				       decoder);

	default:
		break;
	}

	return -pte_bad_context;
}