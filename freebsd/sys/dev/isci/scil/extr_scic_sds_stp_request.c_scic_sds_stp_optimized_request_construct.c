#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* U8 ;
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_7__ {TYPE_1__* task_context_buffer; } ;
struct TYPE_6__ {void* task_type; int /*<<< orphan*/  transfer_length_bytes; } ;
typedef  TYPE_1__ SCU_TASK_CONTEXT_T ;
typedef  scalar_t__ SCI_IO_REQUEST_DATA_DIRECTION ;
typedef  TYPE_2__ SCIC_SDS_REQUEST_T ;

/* Variables and functions */
 scalar_t__ SCI_IO_REQUEST_DATA_OUT ; 
 void* SCU_TASK_TYPE_DMA_IN ; 
 void* SCU_TASK_TYPE_DMA_OUT ; 
 int /*<<< orphan*/  scu_sata_reqeust_construct_task_context (TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static
void scic_sds_stp_optimized_request_construct(
   SCIC_SDS_REQUEST_T * this_request,
   U8                   optimized_task_type,
   U32                  transfer_length,
   SCI_IO_REQUEST_DATA_DIRECTION data_direction
)
{
   SCU_TASK_CONTEXT_T * task_context = this_request->task_context_buffer;

   // Build the STP task context structure
   scu_sata_reqeust_construct_task_context(this_request, task_context);

   // Copy over the number of bytes to be transferred
   task_context->transfer_length_bytes = transfer_length;

   if ( data_direction == SCI_IO_REQUEST_DATA_OUT )
   {
      // The difference between the DMA IN and DMA OUT request task type
      // values are consistent with the difference between FPDMA READ
      // and FPDMA WRITE values.  Add the supplied task type parameter
      // to this difference to set the task type properly for this
      // DATA OUT (WRITE) case.
      task_context->task_type = optimized_task_type + (SCU_TASK_TYPE_DMA_OUT
                                                     - SCU_TASK_TYPE_DMA_IN);
   }
   else
   {
      // For the DATA IN (READ) case, simply save the supplied
      // optimized task type.
      task_context->task_type = optimized_task_type;
   }
}