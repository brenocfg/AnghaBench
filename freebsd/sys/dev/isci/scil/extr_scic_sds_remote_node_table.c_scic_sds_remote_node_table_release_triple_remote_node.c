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
typedef  int U32 ;
typedef  int U16 ;
typedef  int /*<<< orphan*/  SCIC_REMOTE_NODE_TABLE_T ;

/* Variables and functions */
 int SCU_STP_REMOTE_NODE_COUNT ; 
 int /*<<< orphan*/  scic_sds_remote_node_table_set_group (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  scic_sds_remote_node_table_set_group_index (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static
void scic_sds_remote_node_table_release_triple_remote_node(
   SCIC_REMOTE_NODE_TABLE_T * remote_node_table,
   U16                        remote_node_index
)
{
   U32 group_index;

   group_index = remote_node_index / SCU_STP_REMOTE_NODE_COUNT;

   scic_sds_remote_node_table_set_group_index(
      remote_node_table, 2, group_index
   );

   scic_sds_remote_node_table_set_group(remote_node_table, group_index);
}