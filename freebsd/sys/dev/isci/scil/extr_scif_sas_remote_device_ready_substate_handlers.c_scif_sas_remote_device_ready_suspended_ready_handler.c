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
struct TYPE_3__ {int /*<<< orphan*/  ready_substate_machine; } ;
typedef  TYPE_1__ SCIF_SAS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_SAS_REMOTE_DEVICE_READY_SUBSTATE_OPERATIONAL ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void scif_sas_remote_device_ready_suspended_ready_handler(
   SCIF_SAS_REMOTE_DEVICE_T * fw_device
)
{
   sci_base_state_machine_change_state(
      &fw_device->ready_substate_machine,
      SCIF_SAS_REMOTE_DEVICE_READY_SUBSTATE_OPERATIONAL
   );
}