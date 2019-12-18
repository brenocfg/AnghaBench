#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  SCI_BASE_OBJECT_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_REMOTE_DEVICE_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_REMOTE_DEVICE_NOT_READY_START_REQUESTED ; 
 int /*<<< orphan*/  SCI_BASE_REMOTE_DEVICE_STATE_STARTING ; 
 int /*<<< orphan*/  SET_STATE_HANDLER (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_cb_remote_device_not_ready (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * scic_sds_remote_device_get_controller (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_remote_device_state_handler_table ; 

__attribute__((used)) static
void scic_sds_remote_device_starting_state_enter(
   SCI_BASE_OBJECT_T *object
)
{
   SCIC_SDS_CONTROLLER_T    * the_controller;
   SCIC_SDS_REMOTE_DEVICE_T * this_device = (SCIC_SDS_REMOTE_DEVICE_T *)object;

   the_controller = scic_sds_remote_device_get_controller(this_device);

   SET_STATE_HANDLER(
      this_device,
      scic_sds_remote_device_state_handler_table,
      SCI_BASE_REMOTE_DEVICE_STATE_STARTING
   );

   scic_cb_remote_device_not_ready(
      the_controller,
      this_device,
      SCIC_REMOTE_DEVICE_NOT_READY_START_REQUESTED
   );
}