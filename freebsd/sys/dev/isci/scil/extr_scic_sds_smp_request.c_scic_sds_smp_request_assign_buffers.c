#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ was_tag_assigned_by_user; int /*<<< orphan*/  task_context_buffer; int /*<<< orphan*/ * sgl_element_pair_buffer; int /*<<< orphan*/  response_buffer; int /*<<< orphan*/  command_buffer; } ;
typedef  TYPE_1__ SCIC_SDS_REQUEST_T ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  scic_sds_smp_request_get_command_buffer (TYPE_1__*) ; 
 int /*<<< orphan*/  scic_sds_smp_request_get_response_buffer (TYPE_1__*) ; 
 int /*<<< orphan*/  scic_sds_smp_request_get_task_context_buffer (TYPE_1__*) ; 

void scic_sds_smp_request_assign_buffers(
   SCIC_SDS_REQUEST_T *this_request
)
{
   // Assign all of the buffer pointers
   this_request->command_buffer =
      scic_sds_smp_request_get_command_buffer(this_request);
   this_request->response_buffer =
      scic_sds_smp_request_get_response_buffer(this_request);
   this_request->sgl_element_pair_buffer = NULL;

   if (this_request->was_tag_assigned_by_user == FALSE)
   {
      this_request->task_context_buffer =
         scic_sds_smp_request_get_task_context_buffer(this_request);
   }

}