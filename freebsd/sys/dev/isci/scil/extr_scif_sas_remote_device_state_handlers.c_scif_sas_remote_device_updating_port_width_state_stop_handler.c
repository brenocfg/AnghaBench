#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  state_machine; } ;
struct TYPE_5__ {int /*<<< orphan*/  destination_state; TYPE_1__ parent; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_BASE_REMOTE_DEVICE_T ;
typedef  TYPE_2__ SCIF_SAS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_LOG_INFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIF_LOG_OBJECT_REMOTE_DEVICE ; 
 int /*<<< orphan*/  SCIF_SAS_REMOTE_DEVICE_DESTINATION_STATE_STOPPING ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_2__*) ; 
 int /*<<< orphan*/  sci_base_state_machine_get_state (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
SCI_STATUS scif_sas_remote_device_updating_port_width_state_stop_handler(
   SCI_BASE_REMOTE_DEVICE_T * remote_device
)
{
   SCIF_SAS_REMOTE_DEVICE_T * fw_device =
      (SCIF_SAS_REMOTE_DEVICE_T *)remote_device;

   SCIF_LOG_INFO((
      sci_base_object_get_logger(fw_device),
      SCIF_LOG_OBJECT_REMOTE_DEVICE,
      "RemoteDevice:0x%x updating port width state stop handler\n",
      fw_device,
      sci_base_state_machine_get_state(&fw_device->parent.state_machine)
   ));

   //Can't stop the device right now. Remember the pending stopping request.
   //When exit the UPDATING_PORT_WIDTH state, we will check this variable
   //to decide which state to go.
   fw_device->destination_state =
      SCIF_SAS_REMOTE_DEVICE_DESTINATION_STATE_STOPPING;

   return SCI_SUCCESS;
}