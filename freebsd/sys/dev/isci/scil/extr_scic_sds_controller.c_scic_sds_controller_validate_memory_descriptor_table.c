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
struct TYPE_3__ {int completion_queue_entries; int remote_node_entries; int task_context_entries; int /*<<< orphan*/  uf_control; int /*<<< orphan*/ * memory_descriptors; } ;
typedef  int /*<<< orphan*/  SCU_TASK_CONTEXT_T ;
typedef  int /*<<< orphan*/  SCU_REMOTE_NODE_CONTEXT_T ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  TYPE_1__ SCIC_SDS_CONTROLLER_T ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SCI_FAILURE_UNSUPPORTED_INFORMATION_FIELD ; 
 int SCI_MDE_ATTRIBUTE_CACHEABLE ; 
 int SCI_MDE_ATTRIBUTE_PHYSICALLY_CONTIGUOUS ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  SCU_COMPLETION_RAM_ALIGNMENT ; 
 size_t SCU_MDE_COMPLETION_QUEUE ; 
 size_t SCU_MDE_REMOTE_NODE_CONTEXT ; 
 size_t SCU_MDE_TASK_CONTEXT ; 
 size_t SCU_MDE_UF_BUFFER ; 
 int /*<<< orphan*/  SCU_REMOTE_NODE_CONTEXT_ALIGNMENT ; 
 int /*<<< orphan*/  SCU_TASK_CONTEXT_ALIGNMENT ; 
 int /*<<< orphan*/  SCU_UNSOLICITED_FRAME_BUFFER_ALIGNMENT ; 
 scalar_t__ sci_base_mde_is_valid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int scic_sds_unsolicited_frame_control_get_mde_size (int /*<<< orphan*/ ) ; 

SCI_STATUS scic_sds_controller_validate_memory_descriptor_table(
   SCIC_SDS_CONTROLLER_T *this_controller
)
{
   BOOL mde_list_valid;

   mde_list_valid = sci_base_mde_is_valid(
      &this_controller->memory_descriptors[SCU_MDE_COMPLETION_QUEUE],
      SCU_COMPLETION_RAM_ALIGNMENT,
      (sizeof(U32) * this_controller->completion_queue_entries),
      (SCI_MDE_ATTRIBUTE_CACHEABLE | SCI_MDE_ATTRIBUTE_PHYSICALLY_CONTIGUOUS)
   );

   if (mde_list_valid == FALSE)
      return SCI_FAILURE_UNSUPPORTED_INFORMATION_FIELD;

   mde_list_valid = sci_base_mde_is_valid(
      &this_controller->memory_descriptors[SCU_MDE_REMOTE_NODE_CONTEXT],
      SCU_REMOTE_NODE_CONTEXT_ALIGNMENT,
      this_controller->remote_node_entries * sizeof(SCU_REMOTE_NODE_CONTEXT_T),
      SCI_MDE_ATTRIBUTE_PHYSICALLY_CONTIGUOUS
   );

   if (mde_list_valid == FALSE)
      return SCI_FAILURE_UNSUPPORTED_INFORMATION_FIELD;

   mde_list_valid = sci_base_mde_is_valid(
      &this_controller->memory_descriptors[SCU_MDE_TASK_CONTEXT],
      SCU_TASK_CONTEXT_ALIGNMENT,
      this_controller->task_context_entries * sizeof(SCU_TASK_CONTEXT_T),
      SCI_MDE_ATTRIBUTE_PHYSICALLY_CONTIGUOUS
   );

   if (mde_list_valid == FALSE)
      return SCI_FAILURE_UNSUPPORTED_INFORMATION_FIELD;

   mde_list_valid = sci_base_mde_is_valid(
      &this_controller->memory_descriptors[SCU_MDE_UF_BUFFER],
      SCU_UNSOLICITED_FRAME_BUFFER_ALIGNMENT,
      scic_sds_unsolicited_frame_control_get_mde_size(this_controller->uf_control),
      SCI_MDE_ATTRIBUTE_PHYSICALLY_CONTIGUOUS
   );

   if (mde_list_valid == FALSE)
      return SCI_FAILURE_UNSUPPORTED_INFORMATION_FIELD;

   return SCI_SUCCESS;
}