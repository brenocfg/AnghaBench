#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ current_state_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  task_request_count; int /*<<< orphan*/  request_count; TYPE_3__ ready_substate_machine; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/  SCIF_SAS_TASK_REQUEST_T ;
typedef  TYPE_1__ SCIF_SAS_REMOTE_DEVICE_T ;

/* Variables and functions */
 scalar_t__ SCIF_SAS_REMOTE_DEVICE_READY_SUBSTATE_TASK_MGMT ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (TYPE_3__*,scalar_t__) ; 

__attribute__((used)) static
SCI_STATUS scif_sas_remote_device_start_task_request(
   SCIF_SAS_REMOTE_DEVICE_T * fw_device,
   SCIF_SAS_TASK_REQUEST_T  * fw_task
)
{
   // Transition into the TASK MGMT substate if not already in it.
   if (fw_device->ready_substate_machine.current_state_id
       != SCIF_SAS_REMOTE_DEVICE_READY_SUBSTATE_TASK_MGMT)
   {
      sci_base_state_machine_change_state(
         &fw_device->ready_substate_machine,
         SCIF_SAS_REMOTE_DEVICE_READY_SUBSTATE_TASK_MGMT
      );
   }

   fw_device->request_count++;
   fw_device->task_request_count++;

   return SCI_SUCCESS;
}