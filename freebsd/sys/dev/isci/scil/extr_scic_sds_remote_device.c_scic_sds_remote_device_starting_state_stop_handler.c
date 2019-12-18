#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ started_request_count; int /*<<< orphan*/  rnc; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_BASE_REMOTE_DEVICE_T ;
typedef  TYPE_1__ SCIC_SDS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  SCI_BASE_REMOTE_DEVICE_STATE_STOPPING ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_cb_remote_device_rnc_destruct_complete ; 
 int /*<<< orphan*/  scic_sds_remote_device_get_base_state_machine (TYPE_1__*) ; 
 int /*<<< orphan*/  scic_sds_remote_node_context_destruct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static
SCI_STATUS scic_sds_remote_device_starting_state_stop_handler(
   SCI_BASE_REMOTE_DEVICE_T *device
)
{
   SCIC_SDS_REMOTE_DEVICE_T *this_device = (SCIC_SDS_REMOTE_DEVICE_T *)device;

   /*
    * This device has not yet started so there had better be no IO requests
    */
   ASSERT(this_device->started_request_count == 0);

   /*
    * Destroy the remote node context
    */
   scic_sds_remote_node_context_destruct(
      this_device->rnc,
      scic_sds_cb_remote_device_rnc_destruct_complete,
      this_device
   );

   /*
    * Transition to the stopping state and wait for the remote node to
    * complete being posted and invalidated.
    */
   sci_base_state_machine_change_state(
      scic_sds_remote_device_get_base_state_machine(this_device),
      SCI_BASE_REMOTE_DEVICE_STATE_STOPPING
   );

   return SCI_SUCCESS;
}