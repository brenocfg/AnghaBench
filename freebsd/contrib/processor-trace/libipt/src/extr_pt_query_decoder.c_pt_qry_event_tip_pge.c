#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pt_query_decoder {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  ip; } ;
struct TYPE_4__ {TYPE_1__ exec_mode; } ;
struct pt_event {int type; TYPE_2__ variant; } ;

/* Variables and functions */
 int pt_qry_event_ip (int /*<<< orphan*/ *,struct pt_event*,struct pt_query_decoder const*) ; 
 int pte_bad_context ; 
 int pte_internal ; 
#define  ptev_exec_mode 128 

__attribute__((used)) static int pt_qry_event_tip_pge(struct pt_event *ev,
				const struct pt_query_decoder *decoder)
{
	if (!ev)
		return -pte_internal;

	switch (ev->type) {
	case ptev_exec_mode:
		return pt_qry_event_ip(&ev->variant.exec_mode.ip, ev, decoder);

	default:
		break;
	}

	return -pte_bad_context;
}