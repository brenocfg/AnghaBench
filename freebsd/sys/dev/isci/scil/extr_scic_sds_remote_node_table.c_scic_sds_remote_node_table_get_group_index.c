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
struct TYPE_3__ {size_t** remote_node_groups; size_t group_array_size; } ;
typedef  TYPE_1__ SCIC_REMOTE_NODE_TABLE_T ;

/* Variables and functions */
 size_t SCIC_SDS_REMOTE_NODE_TABLE_INVALID_INDEX ; 

__attribute__((used)) static
U32 scic_sds_remote_node_table_get_group_index(
   SCIC_REMOTE_NODE_TABLE_T * remote_node_table,
   U32                        group_table_index
)
{
   U32   dword_index;
   U32 * group_table;
   U32   bit_index;

   group_table = remote_node_table->remote_node_groups[group_table_index];

   for (dword_index = 0; dword_index < remote_node_table->group_array_size; dword_index++)
   {
      if (group_table[dword_index] != 0)
      {
         for (bit_index = 0; bit_index < 32; bit_index++)
         {
            if ((group_table[dword_index] & (1 << bit_index)) != 0)
            {
               return (dword_index * 32) + bit_index;
            }
         }
      }
   }

   return SCIC_SDS_REMOTE_NODE_TABLE_INVALID_INDEX;
}