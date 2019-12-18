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
struct TYPE_3__ {int /*<<< orphan*/  state_machine; } ;
struct TYPE_4__ {scalar_t__ request_count; scalar_t__ destination_state; int /*<<< orphan*/  core_object; TYPE_1__ parent; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_BASE_REQUEST_T ;
typedef  int /*<<< orphan*/  SCI_BASE_REMOTE_DEVICE_T ;
typedef  TYPE_2__ SCIF_SAS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_SAS_REMOTE_DEVICE_CORE_OP_TIMEOUT ; 
 scalar_t__ SCIF_SAS_REMOTE_DEVICE_DESTINATION_STATE_STOPPING ; 
 int /*<<< orphan*/  SCI_BASE_REMOTE_DEVICE_STATE_STOPPING ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_remote_device_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
SCI_STATUS scif_sas_remote_device_updating_port_width_state_complete_io_handler(
   SCI_BASE_REMOTE_DEVICE_T * remote_device,
   SCI_BASE_REQUEST_T       * io_request
)
{
   SCIF_SAS_REMOTE_DEVICE_T * fw_device = (SCIF_SAS_REMOTE_DEVICE_T*)
                                          remote_device;
   fw_device->request_count--;

   //If the request count is zero, go ahead to update the RNC.
   if (fw_device->request_count == 0 )
   {
      if (fw_device->destination_state == SCIF_SAS_REMOTE_DEVICE_DESTINATION_STATE_STOPPING)
      {
         //if the destination state of this device change to STOPPING, no matter
         //whether we need to update the port width, just make the device
         //go to the STOPPING state, the device will be removed anyway.
         sci_base_state_machine_change_state(
            &fw_device->parent.state_machine,
            SCI_BASE_REMOTE_DEVICE_STATE_STOPPING
         );
      }
      else
      {
         //stop the device, upon the stop complete callback, start the device again
         //with the updated port width.
         scic_remote_device_stop(
            fw_device->core_object, SCIF_SAS_REMOTE_DEVICE_CORE_OP_TIMEOUT);
      }
   }

   return SCI_SUCCESS;
}