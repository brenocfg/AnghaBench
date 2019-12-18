#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  state_machine; } ;
struct TYPE_6__ {scalar_t__ destination_state; scalar_t__ device_port_width; TYPE_1__ parent; int /*<<< orphan*/  core_object; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  TYPE_2__ SCIF_SAS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_LOG_INFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIF_LOG_OBJECT_REMOTE_DEVICE ; 
 int /*<<< orphan*/  SCIF_SAS_REMOTE_DEVICE_CORE_OP_TIMEOUT ; 
 scalar_t__ SCIF_SAS_REMOTE_DEVICE_DESTINATION_STATE_STOPPING ; 
 int /*<<< orphan*/  SCI_BASE_REMOTE_DEVICE_STATE_READY ; 
 int /*<<< orphan*/  SCI_BASE_REMOTE_DEVICE_STATE_STOPPING ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_2__*) ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_state_machine_get_state (int /*<<< orphan*/ *) ; 
 scalar_t__ scic_remote_device_get_port_width (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_remote_device_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void scif_sas_remote_device_updating_port_width_state_start_complete_handler(
   SCIF_SAS_REMOTE_DEVICE_T * fw_device,
   SCI_STATUS                 completion_status
)
{
   SCIF_LOG_INFO((
      sci_base_object_get_logger(fw_device),
      SCIF_LOG_OBJECT_REMOTE_DEVICE,
      "RemoteDevice:0x%x updating port width state start complete handler\n",
      fw_device,
      sci_base_state_machine_get_state(&fw_device->parent.state_machine)
   ));

   if ( fw_device->destination_state
           == SCIF_SAS_REMOTE_DEVICE_DESTINATION_STATE_STOPPING )
   {
      //if the destination state of this device change to STOPPING, no matter
      //whether we need to update the port width again, just make the device
      //go to the STOPPING state.
      sci_base_state_machine_change_state(
         &fw_device->parent.state_machine,
         SCI_BASE_REMOTE_DEVICE_STATE_STOPPING
      );
   }
   else if ( scic_remote_device_get_port_width(fw_device->core_object)
                != fw_device->device_port_width
            && fw_device->device_port_width != 0)
   {
      scic_remote_device_stop(
         fw_device->core_object,
         SCIF_SAS_REMOTE_DEVICE_CORE_OP_TIMEOUT
      );
   }
   else
   {
      //Port width updating succeeds. Transfer to destination state.
      sci_base_state_machine_change_state(
         &fw_device->parent.state_machine,
         SCI_BASE_REMOTE_DEVICE_STATE_READY
      );
   }
}