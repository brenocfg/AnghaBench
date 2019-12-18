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
struct TYPE_6__ {int /*<<< orphan*/  state_machine; } ;
struct TYPE_8__ {TYPE_2__* domain; TYPE_1__ parent; } ;
struct TYPE_7__ {int /*<<< orphan*/  controller; } ;
typedef  scalar_t__ SCI_STATUS ;
typedef  TYPE_3__ SCIF_SAS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_LOG_ERROR (int /*<<< orphan*/ ) ; 
 int SCIF_LOG_OBJECT_REMOTE_DEVICE ; 
 int SCIF_LOG_OBJECT_REMOTE_DEVICE_CONFIG ; 
 int /*<<< orphan*/  SCI_BASE_REMOTE_DEVICE_STATE_STOPPED ; 
 int /*<<< orphan*/  SCI_CONTROLLER_REMOTE_DEVICE_ERROR ; 
 scalar_t__ SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_3__*) ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_cb_controller_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void scif_sas_remote_device_stopping_stop_complete_handler(
   SCIF_SAS_REMOTE_DEVICE_T * fw_device,
   SCI_STATUS                 completion_status
)
{
   // Transition directly to the STOPPED state since the core ensures
   // all IO/Tasks are complete.
   sci_base_state_machine_change_state(
      &fw_device->parent.state_machine,
      SCI_BASE_REMOTE_DEVICE_STATE_STOPPED
   );

   if (completion_status != SCI_SUCCESS)
   {
      SCIF_LOG_ERROR((
         sci_base_object_get_logger(fw_device),
         SCIF_LOG_OBJECT_REMOTE_DEVICE | SCIF_LOG_OBJECT_REMOTE_DEVICE_CONFIG,
         "Device:0x%x Status:0x%x failed to stop core device\n",
         fw_device, completion_status
      ));

      // Something is seriously wrong.  Stopping the core remote device
      // shouldn't fail in anyway.
      scif_cb_controller_error(fw_device->domain->controller,
              SCI_CONTROLLER_REMOTE_DEVICE_ERROR);
   }
}