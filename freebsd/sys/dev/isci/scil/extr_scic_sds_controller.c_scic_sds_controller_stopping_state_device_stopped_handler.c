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
struct TYPE_6__ {TYPE_1__ parent; } ;
typedef  int /*<<< orphan*/  SCIC_SDS_REMOTE_DEVICE_T ;
typedef  TYPE_2__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_BASE_CONTROLLER_STATE_STOPPED ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_controller_has_remote_devices_stopping (TYPE_2__*) ; 

__attribute__((used)) static
void scic_sds_controller_stopping_state_device_stopped_handler(
   SCIC_SDS_CONTROLLER_T    * controller,
   SCIC_SDS_REMOTE_DEVICE_T * remote_device
)
{
   if (!scic_sds_controller_has_remote_devices_stopping(controller))
   {
      sci_base_state_machine_change_state(
         &controller->parent.state_machine,
         SCI_BASE_CONTROLLER_STATE_STOPPED
      );
   }
}