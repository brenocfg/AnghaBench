#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ U32 ;
typedef  int U16 ;
typedef  int /*<<< orphan*/  SCIC_REMOTE_NODE_TABLE_T ;

/* Variables and functions */
 int SCIC_SDS_REMOTE_NODE_CONTEXT_INVALID_INDEX ; 
 scalar_t__ SCIC_SDS_REMOTE_NODE_TABLE_INVALID_INDEX ; 
 int SCU_STP_REMOTE_NODE_COUNT ; 
 int /*<<< orphan*/  scic_sds_remote_node_table_clear_group (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  scic_sds_remote_node_table_clear_group_index (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ scic_sds_remote_node_table_get_group_index (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static
U16 scic_sds_remote_node_table_allocate_triple_remote_node(
   SCIC_REMOTE_NODE_TABLE_T * remote_node_table,
   U32                        group_table_index
)
{
   U32 group_index;
   U16 remote_node_index = SCIC_SDS_REMOTE_NODE_CONTEXT_INVALID_INDEX;

   group_index = scic_sds_remote_node_table_get_group_index(
                                             remote_node_table, group_table_index);

   if (group_index != SCIC_SDS_REMOTE_NODE_TABLE_INVALID_INDEX)
   {
      remote_node_index = (U16) group_index * SCU_STP_REMOTE_NODE_COUNT;

      scic_sds_remote_node_table_clear_group_index(
         remote_node_table, group_table_index, group_index
      );

      scic_sds_remote_node_table_clear_group(
         remote_node_table, group_index
      );
   }

   return remote_node_index;
}