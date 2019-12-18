#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  link_arg; int /*<<< orphan*/  (* link ) (int /*<<< orphan*/ ,void*) ;int /*<<< orphan*/  os; } ;
typedef  TYPE_1__ sli4_t ;
struct TYPE_6__ {int speed; int /*<<< orphan*/  topology; int /*<<< orphan*/  status; int /*<<< orphan*/  medium; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ sli4_link_event_t ;
struct TYPE_7__ {int attn_type; int topology; int port_speed; int event_type; int /*<<< orphan*/  event_tag; int /*<<< orphan*/  logical_link_speed; int /*<<< orphan*/  shared_link_status; int /*<<< orphan*/  port_fault; int /*<<< orphan*/  link_number; } ;
typedef  TYPE_3__ sli4_link_attention_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
#define  SLI4_FC_EVENT_LINK_ATTENTION 136 
#define  SLI4_FC_EVENT_SHARED_LINK_ATTENTION 135 
#define  SLI4_LINK_ATTN_FC_AL 134 
#define  SLI4_LINK_ATTN_INTERNAL_LOOPBACK 133 
#define  SLI4_LINK_ATTN_P2P 132 
#define  SLI4_LINK_ATTN_SERDES_LOOPBACK 131 
#define  SLI4_LINK_ATTN_TYPE_LINK_DOWN 130 
#define  SLI4_LINK_ATTN_TYPE_LINK_UP 129 
#define  SLI4_LINK_ATTN_TYPE_NO_HARD_ALPA 128 
 int /*<<< orphan*/  SLI_LINK_MEDIUM_FC ; 
 int /*<<< orphan*/  SLI_LINK_STATUS_DOWN ; 
 int /*<<< orphan*/  SLI_LINK_STATUS_NO_ALPA ; 
 int /*<<< orphan*/  SLI_LINK_STATUS_UP ; 
 int /*<<< orphan*/  SLI_LINK_TOPO_LOOP ; 
 int /*<<< orphan*/  SLI_LINK_TOPO_LOOPBACK_EXTERNAL ; 
 int /*<<< orphan*/  SLI_LINK_TOPO_LOOPBACK_INTERNAL ; 
 int /*<<< orphan*/  SLI_LINK_TOPO_NPORT ; 
 int /*<<< orphan*/  ocs_log_debug (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,void*) ; 

int32_t
sli_fc_process_link_attention(sli4_t *sli4, void *acqe)
{
	sli4_link_attention_t	*link_attn = acqe;
	sli4_link_event_t	event = { 0 };

	ocs_log_debug(sli4->os, "link_number=%d attn_type=%#x topology=%#x port_speed=%#x "
			"port_fault=%#x shared_link_status=%#x logical_link_speed=%#x "
			"event_tag=%#x\n", link_attn->link_number, link_attn->attn_type,
			link_attn->topology, link_attn->port_speed, link_attn->port_fault,
			link_attn->shared_link_status, link_attn->logical_link_speed,
			link_attn->event_tag);

	if (!sli4->link) {
		return 0;
	}

	event.medium   = SLI_LINK_MEDIUM_FC;

	switch (link_attn->attn_type) {
	case SLI4_LINK_ATTN_TYPE_LINK_UP:
		event.status = SLI_LINK_STATUS_UP;
		break;
	case SLI4_LINK_ATTN_TYPE_LINK_DOWN:
		event.status = SLI_LINK_STATUS_DOWN;
		break;
	case SLI4_LINK_ATTN_TYPE_NO_HARD_ALPA:
		ocs_log_debug(sli4->os, "attn_type: no hard alpa\n");
		event.status = SLI_LINK_STATUS_NO_ALPA;
		break;
	default:
		ocs_log_test(sli4->os, "attn_type: unknown\n");
		break;
	}

	switch (link_attn->event_type) {
	case SLI4_FC_EVENT_LINK_ATTENTION:
		break;
	case SLI4_FC_EVENT_SHARED_LINK_ATTENTION:
		ocs_log_debug(sli4->os, "event_type: FC shared link event \n");
		break;
	default:
		ocs_log_test(sli4->os, "event_type: unknown\n");
		break;
	}

	switch (link_attn->topology) {
	case SLI4_LINK_ATTN_P2P:
		event.topology = SLI_LINK_TOPO_NPORT;
		break;
	case SLI4_LINK_ATTN_FC_AL:
		event.topology = SLI_LINK_TOPO_LOOP;
		break;
	case SLI4_LINK_ATTN_INTERNAL_LOOPBACK:
		ocs_log_debug(sli4->os, "topology Internal loopback\n");
		event.topology = SLI_LINK_TOPO_LOOPBACK_INTERNAL;
		break;
	case SLI4_LINK_ATTN_SERDES_LOOPBACK:
		ocs_log_debug(sli4->os, "topology serdes loopback\n");
		event.topology = SLI_LINK_TOPO_LOOPBACK_EXTERNAL;
		break;
	default:
		ocs_log_test(sli4->os, "topology: unknown\n");
		break;
	}

	event.speed    = link_attn->port_speed * 1000;

	sli4->link(sli4->link_arg, (void *)&event);

	return 0;
}