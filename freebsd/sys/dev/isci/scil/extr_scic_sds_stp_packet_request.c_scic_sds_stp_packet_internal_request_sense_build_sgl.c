#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ task_context_buffer; scalar_t__ response_buffer; } ;
struct TYPE_12__ {int /*<<< orphan*/ * data; } ;
struct TYPE_9__ {scalar_t__ address_modifier; int /*<<< orphan*/  length; int /*<<< orphan*/  address_lower; int /*<<< orphan*/  address_upper; } ;
struct TYPE_11__ {int /*<<< orphan*/  B; TYPE_1__ A; } ;
struct TYPE_10__ {int /*<<< orphan*/  transfer_length_bytes; TYPE_3__ sgl_pair_ab; } ;
typedef  TYPE_2__ SCU_TASK_CONTEXT_T ;
typedef  TYPE_3__ SCU_SGL_ELEMENT_PAIR_T ;
typedef  TYPE_4__ SCI_SSP_RESPONSE_IU_T ;
typedef  int /*<<< orphan*/  SCI_PHYSICAL_ADDRESS ;
typedef  TYPE_5__ SCIC_SDS_REQUEST_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCU_SGL_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_cb_physical_address_lower (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_cb_physical_address_upper (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_cb_io_request_get_physical_address (int /*<<< orphan*/ ,TYPE_5__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_request_get_controller (TYPE_5__*) ; 

void scic_sds_stp_packet_internal_request_sense_build_sgl(
   SCIC_SDS_REQUEST_T * this_request
)
{
   void                   *sge;
   SCU_SGL_ELEMENT_PAIR_T *scu_sgl_list   = NULL;
   SCU_TASK_CONTEXT_T     *task_context;
   SCI_PHYSICAL_ADDRESS    physical_address;

   SCI_SSP_RESPONSE_IU_T * rsp_iu =
      (SCI_SSP_RESPONSE_IU_T *)this_request->response_buffer;
   sge =  (void*)&rsp_iu->data[0];

   task_context = (SCU_TASK_CONTEXT_T *)this_request->task_context_buffer;
   scu_sgl_list = &task_context->sgl_pair_ab;

   scic_cb_io_request_get_physical_address(
      scic_sds_request_get_controller(this_request),
      this_request,
      ((char *)sge),
      &physical_address
   );

   scu_sgl_list->A.address_upper = sci_cb_physical_address_upper(physical_address);
   scu_sgl_list->A.address_lower = sci_cb_physical_address_lower(physical_address);
   scu_sgl_list->A.length = task_context->transfer_length_bytes;
   scu_sgl_list->A.address_modifier = 0;

   SCU_SGL_ZERO(scu_sgl_list->B);
}