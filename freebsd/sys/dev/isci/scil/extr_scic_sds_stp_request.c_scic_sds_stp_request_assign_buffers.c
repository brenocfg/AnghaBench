#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ was_tag_assigned_by_user; int /*<<< orphan*/  task_context_buffer; int /*<<< orphan*/  sgl_element_pair_buffer; int /*<<< orphan*/  response_buffer; int /*<<< orphan*/  command_buffer; } ;
struct TYPE_8__ {TYPE_1__ parent; } ;
typedef  TYPE_2__ SCIC_SDS_STP_REQUEST_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_REQUEST_T ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  scic_sds_request_align_sgl_element_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_stp_request_get_h2d_reg_buffer (TYPE_2__*) ; 
 int /*<<< orphan*/  scic_sds_stp_request_get_response_buffer (TYPE_2__*) ; 
 int /*<<< orphan*/  scic_sds_stp_request_get_sgl_element_buffer (TYPE_2__*) ; 
 int /*<<< orphan*/  scic_sds_stp_request_get_task_context_buffer (TYPE_2__*) ; 

void scic_sds_stp_request_assign_buffers(
   SCIC_SDS_REQUEST_T * request
)
{
   SCIC_SDS_STP_REQUEST_T * this_request = (SCIC_SDS_STP_REQUEST_T *)request;

   this_request->parent.command_buffer =
      scic_sds_stp_request_get_h2d_reg_buffer(this_request);
   this_request->parent.response_buffer =
      scic_sds_stp_request_get_response_buffer(this_request);
   this_request->parent.sgl_element_pair_buffer =
      scic_sds_stp_request_get_sgl_element_buffer(this_request);
   this_request->parent.sgl_element_pair_buffer =
      scic_sds_request_align_sgl_element_buffer(this_request->parent.sgl_element_pair_buffer);

   if (this_request->parent.was_tag_assigned_by_user == FALSE)
   {
      this_request->parent.task_context_buffer =
         scic_sds_stp_request_get_task_context_buffer(this_request);
   }
}