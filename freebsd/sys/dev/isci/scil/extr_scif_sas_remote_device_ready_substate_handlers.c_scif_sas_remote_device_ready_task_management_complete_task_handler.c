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
struct TYPE_4__ {scalar_t__ task_request_count; int /*<<< orphan*/  ready_substate_machine; int /*<<< orphan*/  request_count; } ;
struct TYPE_3__ {scalar_t__ affected_request_count; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_BASE_REQUEST_T ;
typedef  int /*<<< orphan*/  SCI_BASE_REMOTE_DEVICE_T ;
typedef  TYPE_1__ SCIF_SAS_TASK_REQUEST_T ;
typedef  TYPE_2__ SCIF_SAS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_SAS_REMOTE_DEVICE_READY_SUBSTATE_OPERATIONAL ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

SCI_STATUS scif_sas_remote_device_ready_task_management_complete_task_handler(
   SCI_BASE_REMOTE_DEVICE_T * remote_device,
   SCI_BASE_REQUEST_T       * task_request
)
{
   SCIF_SAS_REMOTE_DEVICE_T * fw_device = (SCIF_SAS_REMOTE_DEVICE_T*)
                                          remote_device;

   SCIF_SAS_TASK_REQUEST_T * fw_task = (SCIF_SAS_TASK_REQUEST_T *)
                                       task_request;

   fw_device->request_count--;
   fw_device->task_request_count--;

   // All existing task management requests and all of the IO requests
   // affectected by the task management request must complete before
   // the remote device can transition back into the READY / OPERATIONAL
   // state.
   if (  (fw_device->task_request_count == 0)
      && (fw_task->affected_request_count == 0) )
   {
      sci_base_state_machine_change_state(
         &fw_device->ready_substate_machine,
         SCIF_SAS_REMOTE_DEVICE_READY_SUBSTATE_OPERATIONAL
      );
   }

   return SCI_SUCCESS;
}