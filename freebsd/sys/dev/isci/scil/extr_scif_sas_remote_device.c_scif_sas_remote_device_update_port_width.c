#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ U8 ;
struct TYPE_8__ {scalar_t__ current_state_id; } ;
struct TYPE_6__ {TYPE_4__ state_machine; } ;
struct TYPE_7__ {scalar_t__ device_port_width; int /*<<< orphan*/  destination_state; TYPE_1__ parent; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  TYPE_2__ SCIF_SAS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_LOG_INFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIF_LOG_OBJECT_REMOTE_DEVICE ; 
 int /*<<< orphan*/  SCIF_SAS_REMOTE_DEVICE_DESTINATION_STATE_UPDATING_PORT_WIDTH ; 
 scalar_t__ SCI_BASE_REMOTE_DEVICE_STATE_READY ; 
 scalar_t__ SCI_BASE_REMOTE_DEVICE_STATE_STARTING ; 
 int /*<<< orphan*/  SCI_BASE_REMOTE_DEVICE_STATE_UPDATING_PORT_WIDTH ; 
 int /*<<< orphan*/  SCI_FAILURE_INVALID_STATE ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_2__*) ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (TYPE_4__*,int /*<<< orphan*/ ) ; 

SCI_STATUS scif_sas_remote_device_update_port_width(
   SCIF_SAS_REMOTE_DEVICE_T * fw_device,
   U8                         new_port_width
)
{
   SCIF_LOG_INFO((
      sci_base_object_get_logger(fw_device),
      SCIF_LOG_OBJECT_REMOTE_DEVICE,
      "scif_sas_remote_device_update_port_width (0x%x, 0x%x) enter\n",
      fw_device, new_port_width
   ));

   fw_device->device_port_width = new_port_width;

   //Don't Start a new update of port width if a device is already in
   //UPDATING PORT WIDTH state.
   if (fw_device->parent.state_machine.current_state_id == SCI_BASE_REMOTE_DEVICE_STATE_READY)
   {
      if (fw_device->device_port_width != 0)
      {
         //Change state to UPDATING_PORT_WIDTH
         sci_base_state_machine_change_state(
            &fw_device->parent.state_machine,
            SCI_BASE_REMOTE_DEVICE_STATE_UPDATING_PORT_WIDTH
         );
      }

      return SCI_SUCCESS;
   }
   else if (fw_device->parent.state_machine.current_state_id ==
               SCI_BASE_REMOTE_DEVICE_STATE_STARTING)
   {
      fw_device->destination_state =
         SCIF_SAS_REMOTE_DEVICE_DESTINATION_STATE_UPDATING_PORT_WIDTH;
   }

   return SCI_FAILURE_INVALID_STATE;
}