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
struct TYPE_7__ {void* bounce; void* rnode; void* unsolicited; void* port; void* domain; } ;
struct TYPE_6__ {void* bounce; void* rnode; void* unsolicited; void* port; void* domain; } ;
struct TYPE_8__ {int /*<<< orphan*/  os; TYPE_2__ args; TYPE_1__ callback; } ;
typedef  TYPE_3__ ocs_hw_t ;
typedef  int /*<<< orphan*/  ocs_hw_rtn_e ;
typedef  int ocs_hw_callback_e ;

/* Variables and functions */
#define  OCS_HW_CB_BOUNCE 132 
#define  OCS_HW_CB_DOMAIN 131 
 int OCS_HW_CB_MAX ; 
#define  OCS_HW_CB_PORT 130 
#define  OCS_HW_CB_REMOTE_NODE 129 
#define  OCS_HW_CB_UNSOLICITED 128 
 int /*<<< orphan*/  OCS_HW_RTN_ERROR ; 
 int /*<<< orphan*/  OCS_HW_RTN_SUCCESS ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ *,char*,TYPE_3__*,int,void*) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*,int) ; 

ocs_hw_rtn_e
ocs_hw_callback(ocs_hw_t *hw, ocs_hw_callback_e which, void *func, void *arg)
{

	if (!hw || !func || (which >= OCS_HW_CB_MAX)) {
		ocs_log_err(NULL, "bad parameter hw=%p which=%#x func=%p\n",
			    hw, which, func);
		return OCS_HW_RTN_ERROR;
	}

	switch (which) {
	case OCS_HW_CB_DOMAIN:
		hw->callback.domain = func;
		hw->args.domain = arg;
		break;
	case OCS_HW_CB_PORT:
		hw->callback.port = func;
		hw->args.port = arg;
		break;
	case OCS_HW_CB_UNSOLICITED:
		hw->callback.unsolicited = func;
		hw->args.unsolicited = arg;
		break;
	case OCS_HW_CB_REMOTE_NODE:
		hw->callback.rnode = func;
		hw->args.rnode = arg;
		break;
	case OCS_HW_CB_BOUNCE:
		hw->callback.bounce = func;
		hw->args.bounce = arg;
		break;
	default:
		ocs_log_test(hw->os, "unknown callback %#x\n", which);
		return OCS_HW_RTN_ERROR;
	}

	return OCS_HW_RTN_SUCCESS;
}