#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  fip_arg; int /*<<< orphan*/  (* fip ) (int /*<<< orphan*/ ,TYPE_2__*) ;int /*<<< orphan*/  os; } ;
typedef  TYPE_1__ sli4_t ;
struct TYPE_7__ {int type; int index; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ sli4_fip_event_t ;
struct TYPE_8__ {int event_type; int event_information; int /*<<< orphan*/  event_tag; int /*<<< orphan*/  fcf_count; } ;
typedef  TYPE_3__ sli4_fcoe_fip_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
#define  SLI4_FCOE_FIP_FCF_CLEAR_VLINK 132 
#define  SLI4_FCOE_FIP_FCF_DEAD 131 
#define  SLI4_FCOE_FIP_FCF_DISCOVERED 130 
#define  SLI4_FCOE_FIP_FCF_MODIFIED 129 
#define  SLI4_FCOE_FIP_FCF_TABLE_FULL 128 
 int UINT16_MAX ; 
 void* UINT32_MAX ; 
 int /*<<< orphan*/  ocs_log_debug (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*) ; 

int32_t
sli_fc_process_fcoe(sli4_t *sli4, void *acqe)
{
	sli4_fcoe_fip_t	*fcoe = acqe;
	sli4_fip_event_t event = { 0 };
	uint32_t	mask = UINT32_MAX;

	ocs_log_debug(sli4->os, "ACQE FCoE FIP type=%02x count=%d tag=%#x\n",
			fcoe->event_type,
			fcoe->fcf_count,
			fcoe->event_tag);

	if (!sli4->fip) {
		return 0;
	}

	event.type = fcoe->event_type;
	event.index = UINT32_MAX;

	switch (fcoe->event_type) {
	case SLI4_FCOE_FIP_FCF_DISCOVERED:
		ocs_log_debug(sli4->os, "FCF Discovered index=%d\n", fcoe->event_information);
		break;
	case SLI4_FCOE_FIP_FCF_TABLE_FULL:
		ocs_log_debug(sli4->os, "FCF Table Full\n");
		mask = 0;
		break;
	case SLI4_FCOE_FIP_FCF_DEAD:
		ocs_log_debug(sli4->os, "FCF Dead/Gone index=%d\n", fcoe->event_information);
		break;
	case SLI4_FCOE_FIP_FCF_CLEAR_VLINK:
		mask = UINT16_MAX;
		ocs_log_debug(sli4->os, "Clear VLINK Received VPI=%#x\n", fcoe->event_information & mask);
		break;
	case SLI4_FCOE_FIP_FCF_MODIFIED:
		ocs_log_debug(sli4->os, "FCF Modified\n");
		break;
	default:
		ocs_log_test(sli4->os, "bad FCoE type %#x", fcoe->event_type);
		mask = 0;
	}

	if (mask != 0) {
		event.index = fcoe->event_information & mask;
	}

	sli4->fip(sli4->fip_arg, &event);

	return 0;
}