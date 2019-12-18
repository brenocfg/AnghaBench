#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {size_t remote_node_index; } ;
struct TYPE_11__ {int /*<<< orphan*/ * remote_device_sequence; } ;
struct TYPE_10__ {TYPE_3__* rnc; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_BASE_REMOTE_DEVICE_T ;
typedef  TYPE_1__ SCIC_SDS_REMOTE_DEVICE_T ;
typedef  TYPE_2__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_SDS_REMOTE_NODE_CONTEXT_INVALID_INDEX ; 
 int /*<<< orphan*/  SCI_BASE_REMOTE_DEVICE_STATE_FINAL ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_controller_free_remote_node_context (TYPE_2__*,TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  scic_sds_remote_device_deinitialize_state_logging (TYPE_1__*) ; 
 int /*<<< orphan*/  scic_sds_remote_device_get_base_state_machine (TYPE_1__*) ; 
 TYPE_2__* scic_sds_remote_device_get_controller (TYPE_1__*) ; 
 int /*<<< orphan*/  scic_sds_remote_node_context_set_remote_node_index (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
SCI_STATUS scic_sds_remote_device_stopped_state_destruct_handler(
   SCI_BASE_REMOTE_DEVICE_T *device
)
{
   SCIC_SDS_REMOTE_DEVICE_T *this_device = (SCIC_SDS_REMOTE_DEVICE_T *)device;

   SCIC_SDS_CONTROLLER_T * the_controller =
      scic_sds_remote_device_get_controller(this_device);

   the_controller->remote_device_sequence[this_device->rnc->remote_node_index]++;

   scic_sds_controller_free_remote_node_context(
      the_controller,
      this_device,
      this_device->rnc->remote_node_index
   );

   scic_sds_remote_node_context_set_remote_node_index(
      this_device->rnc,
      SCIC_SDS_REMOTE_NODE_CONTEXT_INVALID_INDEX
   );

   sci_base_state_machine_change_state(
      scic_sds_remote_device_get_base_state_machine(this_device),
      SCI_BASE_REMOTE_DEVICE_STATE_FINAL
   );

   scic_sds_remote_device_deinitialize_state_logging(this_device);

   return SCI_SUCCESS;
}