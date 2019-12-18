#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  ready_substate_machine; scalar_t__ has_ready_substate_machine; } ;
typedef  int /*<<< orphan*/  SCI_BASE_OBJECT_T ;
typedef  TYPE_1__ SCIC_SDS_REMOTE_DEVICE_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_BASE_REMOTE_DEVICE_STATE_READY ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  SET_STATE_HANDLER (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_state_machine_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_cb_remote_device_ready (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  scic_cb_remote_device_start_complete (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_controller_remote_device_started (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * scic_sds_remote_device_get_controller (TYPE_1__*) ; 
 int /*<<< orphan*/  scic_sds_remote_device_state_handler_table ; 

__attribute__((used)) static
void scic_sds_remote_device_ready_state_enter(
   SCI_BASE_OBJECT_T *object
)
{
   SCIC_SDS_CONTROLLER_T    * the_controller;
   SCIC_SDS_REMOTE_DEVICE_T * this_device = (SCIC_SDS_REMOTE_DEVICE_T *)object;

   the_controller = scic_sds_remote_device_get_controller(this_device);

   SET_STATE_HANDLER(
      this_device,
      scic_sds_remote_device_state_handler_table,
      SCI_BASE_REMOTE_DEVICE_STATE_READY
   );

   /// @todo Check the device object for the proper return code for this
   ///       callback
   scic_cb_remote_device_start_complete(
      the_controller, this_device, SCI_SUCCESS
   );

   scic_sds_controller_remote_device_started(
      the_controller, this_device
   );

   if (this_device->has_ready_substate_machine)
   {
      sci_base_state_machine_start(&this_device->ready_substate_machine);
   }
   else
   {
      scic_cb_remote_device_ready(the_controller, this_device);
   }
}