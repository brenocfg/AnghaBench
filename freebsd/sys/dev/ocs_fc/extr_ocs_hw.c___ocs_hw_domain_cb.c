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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {scalar_t__ status; } ;
typedef  TYPE_1__ sli4_mbox_command_header_t ;
typedef  int /*<<< orphan*/  ocs_sm_event_t ;
struct TYPE_6__ {int /*<<< orphan*/  os; } ;
typedef  TYPE_2__ ocs_hw_t ;
struct TYPE_7__ {int /*<<< orphan*/  sm; int /*<<< orphan*/  indicator; } ;
typedef  TYPE_3__ ocs_domain_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_EVT_ERROR ; 
 int /*<<< orphan*/  OCS_EVT_RESPONSE ; 
 int /*<<< orphan*/  ocs_log_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ocs_sm_post_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int32_t
__ocs_hw_domain_cb(ocs_hw_t *hw, int32_t status, uint8_t *mqe, void *arg)
{
	ocs_domain_t	*domain = arg;
	sli4_mbox_command_header_t	*hdr = (sli4_mbox_command_header_t *)mqe;
	ocs_sm_event_t	evt;

	if (status || hdr->status) {
		ocs_log_debug(hw->os, "bad status vfi=%#x st=%x hdr=%x\n",
			      domain->indicator, status, hdr->status);
		evt = OCS_EVT_ERROR;
	} else {
		evt = OCS_EVT_RESPONSE;
	}

	ocs_sm_post_event(&domain->sm, evt, mqe);

	return 0;
}