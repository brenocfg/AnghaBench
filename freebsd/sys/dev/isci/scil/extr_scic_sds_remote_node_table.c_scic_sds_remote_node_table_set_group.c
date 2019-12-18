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
typedef  size_t U32 ;
struct TYPE_3__ {size_t available_nodes_array_size; size_t* available_remote_nodes; } ;
typedef  TYPE_1__ SCIC_REMOTE_NODE_TABLE_T ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 size_t SCIC_SDS_REMOTE_NODE_SETS_PER_DWORD ; 
 size_t SCIC_SDS_REMOTE_NODE_TABLE_FULL_SLOT_VALUE ; 
 size_t SCU_STP_REMOTE_NODE_COUNT ; 

__attribute__((used)) static
void scic_sds_remote_node_table_set_group(
   SCIC_REMOTE_NODE_TABLE_T * remote_node_table,
   U32                        group_index
)
{
   U32 dword_location;
   U32 dword_remainder;
   U32 dword_value;

   ASSERT(
        (remote_node_table->available_nodes_array_size * SCIC_SDS_REMOTE_NODE_SETS_PER_DWORD)
      > (group_index / SCU_STP_REMOTE_NODE_COUNT)
   );

   dword_location  = group_index / SCIC_SDS_REMOTE_NODE_SETS_PER_DWORD;
   dword_remainder = group_index % SCIC_SDS_REMOTE_NODE_SETS_PER_DWORD;

   dword_value = remote_node_table->available_remote_nodes[dword_location];
   dword_value |= (SCIC_SDS_REMOTE_NODE_TABLE_FULL_SLOT_VALUE << (dword_remainder * 4));
   remote_node_table->available_remote_nodes[dword_location] = dword_value;
}