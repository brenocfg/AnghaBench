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
struct TYPE_6__ {scalar_t__ link_type; int port_link_status; int port_speed; } ;
typedef  TYPE_2__ sli4_link_state_t ;
struct TYPE_7__ {int speed; int /*<<< orphan*/  status; int /*<<< orphan*/  medium; int /*<<< orphan*/  topology; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ sli4_link_event_t ;
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ SLI4_LINK_TYPE_ETHERNET ; 
#define  SLI4_PORT_LINK_STATUS_LOGICAL_DOWN 131 
#define  SLI4_PORT_LINK_STATUS_LOGICAL_UP 130 
#define  SLI4_PORT_LINK_STATUS_PHYSICAL_DOWN 129 
#define  SLI4_PORT_LINK_STATUS_PHYSICAL_UP 128 
 int /*<<< orphan*/  SLI_LINK_MEDIUM_ETHERNET ; 
 int /*<<< orphan*/  SLI_LINK_MEDIUM_MAX ; 
 int /*<<< orphan*/  SLI_LINK_STATUS_DOWN ; 
 int /*<<< orphan*/  SLI_LINK_STATUS_MAX ; 
 int /*<<< orphan*/  SLI_LINK_STATUS_UP ; 
 int /*<<< orphan*/  SLI_LINK_TOPO_MAX ; 
 int /*<<< orphan*/  SLI_LINK_TOPO_NPORT ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,void*) ; 

int32_t
sli_fc_process_link_state(sli4_t *sli4, void *acqe)
{
	sli4_link_state_t	*link_state = acqe;
	sli4_link_event_t	event = { 0 };
	int32_t			rc = 0;

	if (!sli4->link) {
		/* bail if there is no callback */
		return 0;
	}

	if (SLI4_LINK_TYPE_ETHERNET == link_state->link_type) {
		event.topology = SLI_LINK_TOPO_NPORT;
		event.medium   = SLI_LINK_MEDIUM_ETHERNET;
	} else {
		/* TODO is this supported for anything other than FCoE? */
		ocs_log_test(sli4->os, "unsupported link type %#x\n",
				link_state->link_type);
		event.topology = SLI_LINK_TOPO_MAX;
		event.medium   = SLI_LINK_MEDIUM_MAX;
		rc = -1;
	}

	switch (link_state->port_link_status) {
	case SLI4_PORT_LINK_STATUS_PHYSICAL_DOWN:
	case SLI4_PORT_LINK_STATUS_LOGICAL_DOWN:
		event.status = SLI_LINK_STATUS_DOWN;
		break;
	case SLI4_PORT_LINK_STATUS_PHYSICAL_UP:
	case SLI4_PORT_LINK_STATUS_LOGICAL_UP:
		event.status = SLI_LINK_STATUS_UP;
		break;
	default:
		ocs_log_test(sli4->os, "unsupported link status %#x\n",
				link_state->port_link_status);
		event.status = SLI_LINK_STATUS_MAX;
		rc = -1;
	}

	switch (link_state->port_speed) {
	case 0:
		event.speed = 0;
		break;
	case 1:
		event.speed = 10;
		break;
	case 2:
		event.speed = 100;
		break;
	case 3:
		event.speed = 1000;
		break;
	case 4:
		event.speed = 10000;
		break;
	case 5:
		event.speed = 20000;
		break;
	case 6:
		event.speed = 25000;
		break;
	case 7:
		event.speed = 40000;
		break;
	case 8:
		event.speed = 100000;
		break;
	default:
		ocs_log_test(sli4->os, "unsupported port_speed %#x\n",
				link_state->port_speed);
		rc = -1;
	}

	sli4->link(sli4->link_arg, (void *)&event);

	return rc;
}