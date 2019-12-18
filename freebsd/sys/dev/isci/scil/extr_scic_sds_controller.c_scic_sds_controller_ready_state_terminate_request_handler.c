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
typedef  scalar_t__ SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_BASE_REQUEST_T ;
typedef  int /*<<< orphan*/  SCI_BASE_REMOTE_DEVICE_T ;
typedef  int /*<<< orphan*/  SCI_BASE_CONTROLLER_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_REQUEST_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 scalar_t__ SCI_SUCCESS ; 
 int SCU_CONTEXT_COMMAND_REQUEST_POST_TC_ABORT ; 
 int /*<<< orphan*/  scic_sds_controller_post_request (int /*<<< orphan*/ *,int) ; 
 scalar_t__ scic_sds_io_request_terminate (int /*<<< orphan*/ *) ; 
 int scic_sds_request_get_post_context (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
SCI_STATUS scic_sds_controller_ready_state_terminate_request_handler(
   SCI_BASE_CONTROLLER_T    *controller,
   SCI_BASE_REMOTE_DEVICE_T *remote_device,
   SCI_BASE_REQUEST_T       *io_request
)
{
   SCIC_SDS_CONTROLLER_T    *this_controller = (SCIC_SDS_CONTROLLER_T *)
                                               controller;
   SCIC_SDS_REQUEST_T       *the_request     = (SCIC_SDS_REQUEST_T *)
                                               io_request;
   SCI_STATUS                status;

   status = scic_sds_io_request_terminate(the_request);
   if (status == SCI_SUCCESS)
   {
      // Utilize the original post context command and or in the POST_TC_ABORT
      // request sub-type.
      scic_sds_controller_post_request(
         this_controller,
         scic_sds_request_get_post_context(the_request)
         | SCU_CONTEXT_COMMAND_REQUEST_POST_TC_ABORT
      );
   }

   return status;
}