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
typedef  int U32 ;
struct TYPE_3__ {int available_nodes_array_size; int* available_remote_nodes; } ;
typedef  TYPE_1__ SCIC_REMOTE_NODE_TABLE_T ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int SCIC_SDS_REMOTE_NODES_PER_DWORD ; 
 int SCIC_SDS_REMOTE_NODE_SETS_PER_DWORD ; 
 int SCU_STP_REMOTE_NODE_COUNT ; 

__attribute__((used)) static
void scic_sds_remote_node_table_clear_node_index(
   SCIC_REMOTE_NODE_TABLE_T * remote_node_table,
   U32                        remote_node_index
)
{
   U32 dword_location;
   U32 dword_remainder;
   U32 slot_position;
   U32 slot_normalized;

   ASSERT(
        (remote_node_table->available_nodes_array_size * SCIC_SDS_REMOTE_NODE_SETS_PER_DWORD)
      > (remote_node_index / SCU_STP_REMOTE_NODE_COUNT)
   );

   dword_location  = remote_node_index / SCIC_SDS_REMOTE_NODES_PER_DWORD;
   dword_remainder = remote_node_index % SCIC_SDS_REMOTE_NODES_PER_DWORD;
   slot_normalized = (dword_remainder / SCU_STP_REMOTE_NODE_COUNT) * sizeof(U32);
   slot_position   = remote_node_index % SCU_STP_REMOTE_NODE_COUNT;

   remote_node_table->available_remote_nodes[dword_location] &=
      ~(1 << (slot_normalized + slot_position));
}