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
typedef  int /*<<< orphan*/  U32 ;
typedef  size_t U16 ;
struct TYPE_3__ {int /*<<< orphan*/ ** device_table; int /*<<< orphan*/  available_remote_nodes; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/  SCIC_SDS_REMOTE_DEVICE_T ;
typedef  TYPE_1__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 size_t SCIC_SDS_REMOTE_NODE_CONTEXT_INVALID_INDEX ; 
 int /*<<< orphan*/  SCI_FAILURE_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  scic_sds_remote_device_node_count (int /*<<< orphan*/ *) ; 
 size_t scic_sds_remote_node_table_allocate_remote_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

SCI_STATUS scic_sds_controller_allocate_remote_node_context(
   SCIC_SDS_CONTROLLER_T    * this_controller,
   SCIC_SDS_REMOTE_DEVICE_T * the_device,
   U16                      * node_id
)
{
   U16 node_index;
   U32 remote_node_count = scic_sds_remote_device_node_count(the_device);

   node_index = scic_sds_remote_node_table_allocate_remote_node(
                  &this_controller->available_remote_nodes, remote_node_count
              );

   if (node_index != SCIC_SDS_REMOTE_NODE_CONTEXT_INVALID_INDEX)
   {
      this_controller->device_table[node_index] = the_device;

      *node_id = node_index;

      return SCI_SUCCESS;
   }

   return SCI_FAILURE_INSUFFICIENT_RESOURCES;
}