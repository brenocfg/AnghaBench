#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ U32 ;
struct TYPE_6__ {int /*<<< orphan*/  frame_type; } ;
struct TYPE_7__ {TYPE_1__ ssp; } ;
struct TYPE_8__ {int ssp_command_iu_length; scalar_t__ transfer_length_bytes; int /*<<< orphan*/  task_type; TYPE_2__ type; } ;
typedef  TYPE_3__ SCU_TASK_CONTEXT_T ;
typedef  int /*<<< orphan*/  SCI_SSP_COMMAND_IU_T ;
typedef  int SCI_IO_REQUEST_DATA_DIRECTION ;
typedef  int /*<<< orphan*/  SCIC_SDS_REQUEST_T ;

/* Variables and functions */
#define  SCI_IO_REQUEST_DATA_IN 130 
#define  SCI_IO_REQUEST_DATA_OUT 129 
#define  SCI_IO_REQUEST_NO_DATA 128 
 int /*<<< orphan*/  SCI_SAS_COMMAND_FRAME ; 
 int /*<<< orphan*/  SCU_TASK_TYPE_IOREAD ; 
 int /*<<< orphan*/  SCU_TASK_TYPE_IOWRITE ; 
 int /*<<< orphan*/  scic_sds_request_build_sgl (int /*<<< orphan*/ *) ; 
 TYPE_3__* scic_sds_request_get_task_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scu_ssp_reqeust_construct_task_context (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static
void scu_ssp_io_request_construct_task_context(
   SCIC_SDS_REQUEST_T *this_request,
   SCI_IO_REQUEST_DATA_DIRECTION data_direction,
   U32 transfer_length_bytes
)
{
   SCU_TASK_CONTEXT_T *task_context;

   task_context = scic_sds_request_get_task_context(this_request);

   scu_ssp_reqeust_construct_task_context(this_request, task_context);

   task_context->ssp_command_iu_length = sizeof(SCI_SSP_COMMAND_IU_T) / sizeof(U32);
   task_context->type.ssp.frame_type = SCI_SAS_COMMAND_FRAME;

   switch (data_direction)
   {
   case SCI_IO_REQUEST_DATA_IN:
   case SCI_IO_REQUEST_NO_DATA:
      task_context->task_type = SCU_TASK_TYPE_IOREAD;
      break;
   case SCI_IO_REQUEST_DATA_OUT:
      task_context->task_type = SCU_TASK_TYPE_IOWRITE;
      break;
   }

   task_context->transfer_length_bytes = transfer_length_bytes;

   if (task_context->transfer_length_bytes > 0)
   {
      scic_sds_request_build_sgl(this_request);
   }
}