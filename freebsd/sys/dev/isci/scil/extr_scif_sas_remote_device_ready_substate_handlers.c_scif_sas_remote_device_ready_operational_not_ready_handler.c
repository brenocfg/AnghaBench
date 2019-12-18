#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ U32 ;
struct TYPE_3__ {int /*<<< orphan*/  ready_substate_machine; } ;
typedef  TYPE_1__ SCIF_SAS_REMOTE_DEVICE_T ;

/* Variables and functions */
 scalar_t__ SCIC_REMOTE_DEVICE_NOT_READY_SATA_SDB_ERROR_FIS_RECEIVED ; 
 int /*<<< orphan*/  SCIF_SAS_REMOTE_DEVICE_READY_SUBSTATE_NCQ_ERROR ; 
 int /*<<< orphan*/  SCIF_SAS_REMOTE_DEVICE_READY_SUBSTATE_SUSPENDED ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void scif_sas_remote_device_ready_operational_not_ready_handler(
   SCIF_SAS_REMOTE_DEVICE_T * fw_device,
   U32                        reason_code
)
{
   if (reason_code == SCIC_REMOTE_DEVICE_NOT_READY_SATA_SDB_ERROR_FIS_RECEIVED)
   {
      sci_base_state_machine_change_state(
         &fw_device->ready_substate_machine,
         SCIF_SAS_REMOTE_DEVICE_READY_SUBSTATE_NCQ_ERROR
      );
   }
   else
   {
      // Even though we are in the OPERATIONAL state, the core remote device is not
      // ready.  As a result, we process user requests/events as if we were
      // stopping the framework remote device.
      sci_base_state_machine_change_state(
         &fw_device->ready_substate_machine,
         SCIF_SAS_REMOTE_DEVICE_READY_SUBSTATE_SUSPENDED
      );
   }
}