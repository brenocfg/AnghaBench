#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* state_handlers; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* remote_device_started_handler ) (TYPE_2__*,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  SCIC_SDS_REMOTE_DEVICE_T ;
typedef  TYPE_2__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_LOG_INFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIC_LOG_OBJECT_CONTROLLER ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_2__*) ; 
 int /*<<< orphan*/  sci_base_state_machine_get_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_controller_get_base_state_machine (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *) ; 

void scic_sds_controller_remote_device_started(
   SCIC_SDS_CONTROLLER_T    * this_controller,
   SCIC_SDS_REMOTE_DEVICE_T * the_device
)
{
   if (this_controller->state_handlers->remote_device_started_handler != NULL)
   {
      this_controller->state_handlers->remote_device_started_handler(
         this_controller, the_device
      );
   }
   else
   {
      SCIC_LOG_INFO((
         sci_base_object_get_logger(this_controller),
         SCIC_LOG_OBJECT_CONTROLLER,
         "SCIC Controller 0x%x remote device started event from device 0x%x in unexpected state %d\n",
         this_controller,
         the_device,
         sci_base_state_machine_get_state(
            scic_sds_controller_get_base_state_machine(this_controller))
      ));
   }
}