#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_5__ {int /*<<< orphan*/  user_request; scalar_t__ response_buffer; } ;
struct TYPE_4__ {int /*<<< orphan*/  data; int /*<<< orphan*/  response_data_length; } ;
typedef  TYPE_1__ SCI_SSP_RESPONSE_IU_T ;
typedef  TYPE_2__ SCIC_SDS_REQUEST_T ;

/* Variables and functions */
 int /*<<< orphan*/  MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_ssp_get_response_data_length (int /*<<< orphan*/ ) ; 
 void* scic_cb_ssp_task_request_get_response_data_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_cb_ssp_task_request_get_response_data_length (int /*<<< orphan*/ ) ; 

void scic_sds_io_request_copy_response(
   SCIC_SDS_REQUEST_T *this_request
)
{
   void                  * response_buffer;
   U32                     user_response_length;
   U32                     core_response_length;
   SCI_SSP_RESPONSE_IU_T * ssp_response;

   ssp_response = (SCI_SSP_RESPONSE_IU_T *)this_request->response_buffer;

   response_buffer = scic_cb_ssp_task_request_get_response_data_address(
                        this_request->user_request
                     );

   user_response_length = scic_cb_ssp_task_request_get_response_data_length(
                        this_request->user_request
                     );

   core_response_length = sci_ssp_get_response_data_length(
                           ssp_response->response_data_length
                     );

   user_response_length = MIN(user_response_length, core_response_length);

   memcpy(response_buffer, ssp_response->data, user_response_length);
}