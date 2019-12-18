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
struct TYPE_3__ {scalar_t__ request_count; int /*<<< orphan*/  core_object; int /*<<< orphan*/  destination_state; } ;
typedef  int /*<<< orphan*/  SCI_BASE_OBJECT_T ;
typedef  TYPE_1__ SCIF_SAS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_SAS_REMOTE_DEVICE_CORE_OP_TIMEOUT ; 
 int /*<<< orphan*/  SCIF_SAS_REMOTE_DEVICE_DESTINATION_STATE_READY ; 
 int /*<<< orphan*/  SCI_BASE_REMOTE_DEVICE_STATE_UPDATING_PORT_WIDTH ; 
 int /*<<< orphan*/  SET_STATE_HANDLER (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_remote_device_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_sas_remote_device_state_handler_table ; 

__attribute__((used)) static
void scif_sas_remote_device_updating_port_width_state_enter(
   SCI_BASE_OBJECT_T *object
)
{
   SCIF_SAS_REMOTE_DEVICE_T * fw_device = (SCIF_SAS_REMOTE_DEVICE_T *)object;

   SET_STATE_HANDLER(
      fw_device,
      scif_sas_remote_device_state_handler_table,
      SCI_BASE_REMOTE_DEVICE_STATE_UPDATING_PORT_WIDTH
   );

   fw_device->destination_state = SCIF_SAS_REMOTE_DEVICE_DESTINATION_STATE_READY;

   //If the request count is zero, go ahead to update the RNC.
   //If not, don't do anything for now. The IO complete handler of this state
   //will update the RNC whenever the request count goes down to zero.
   if (fw_device->request_count == 0)
   {
      //stop the device, upon the stop complete callback, start the device again
      //with the updated port width.
      scic_remote_device_stop(
         fw_device->core_object, SCIF_SAS_REMOTE_DEVICE_CORE_OP_TIMEOUT);
   }
}