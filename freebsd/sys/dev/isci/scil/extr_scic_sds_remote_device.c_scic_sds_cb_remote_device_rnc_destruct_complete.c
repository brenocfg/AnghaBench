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
struct TYPE_3__ {scalar_t__ started_request_count; } ;
typedef  TYPE_1__ SCIC_SDS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  SCI_BASE_REMOTE_DEVICE_STATE_STOPPED ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_remote_device_get_base_state_machine (TYPE_1__*) ; 

__attribute__((used)) static
void scic_sds_cb_remote_device_rnc_destruct_complete(
   void * user_parameter
)
{
   SCIC_SDS_REMOTE_DEVICE_T * this_device;
   this_device = (SCIC_SDS_REMOTE_DEVICE_T *)user_parameter;

   ASSERT(this_device->started_request_count == 0);

   sci_base_state_machine_change_state(
      scic_sds_remote_device_get_base_state_machine(this_device),
      SCI_BASE_REMOTE_DEVICE_STATE_STOPPED
   );
}