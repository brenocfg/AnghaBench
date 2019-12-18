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
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_7__ {int /*<<< orphan*/  frame_type; } ;
struct TYPE_6__ {TYPE_2__ ssp; } ;
struct TYPE_8__ {int control_frame; int ssp_command_iu_length; TYPE_1__ type; scalar_t__ transfer_length_bytes; int /*<<< orphan*/  task_type; int /*<<< orphan*/  priority; } ;
typedef  TYPE_3__ SCU_TASK_CONTEXT_T ;
typedef  int /*<<< orphan*/  SCI_SSP_TASK_IU_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_REQUEST_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_SAS_TASK_FRAME ; 
 int /*<<< orphan*/  SCU_TASK_PRIORITY_HIGH ; 
 int /*<<< orphan*/  SCU_TASK_TYPE_RAW_FRAME ; 
 TYPE_3__* scic_sds_request_get_task_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scu_ssp_reqeust_construct_task_context (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static
void scu_ssp_task_request_construct_task_context(
   SCIC_SDS_REQUEST_T *this_request
)
{
   SCU_TASK_CONTEXT_T *task_context;

   task_context = scic_sds_request_get_task_context(this_request);

   scu_ssp_reqeust_construct_task_context(this_request, task_context);

   task_context->control_frame                = 1;
   task_context->priority                     = SCU_TASK_PRIORITY_HIGH;
   task_context->task_type                    = SCU_TASK_TYPE_RAW_FRAME;
   task_context->transfer_length_bytes        = 0;
   task_context->type.ssp.frame_type          = SCI_SAS_TASK_FRAME;
   task_context->ssp_command_iu_length = sizeof(SCI_SSP_TASK_IU_T) / sizeof(U32);
}