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
typedef  int /*<<< orphan*/  U16 ;
struct TYPE_8__ {TYPE_1__** io_request_table; } ;
struct TYPE_7__ {int /*<<< orphan*/  io_tag; } ;
typedef  scalar_t__ SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_BASE_REQUEST_T ;
typedef  int /*<<< orphan*/  SCI_BASE_REMOTE_DEVICE_T ;
typedef  int /*<<< orphan*/  SCI_BASE_CONTROLLER_T ;
typedef  TYPE_1__ SCIC_SDS_REQUEST_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_REMOTE_DEVICE_T ;
typedef  TYPE_2__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 scalar_t__ SCI_FAILURE_RESET_DEVICE_PARTIAL_SUCCESS ; 
 scalar_t__ SCI_SUCCESS ; 
 int /*<<< orphan*/  scic_sds_controller_post_request (TYPE_2__*,int /*<<< orphan*/ ) ; 
 size_t scic_sds_io_tag_get_index (int /*<<< orphan*/ ) ; 
 scalar_t__ scic_sds_remote_device_start_task (TYPE_2__*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  scic_sds_request_get_post_context (TYPE_1__*) ; 

__attribute__((used)) static
SCI_STATUS scic_sds_controller_ready_state_start_task_handler(
   SCI_BASE_CONTROLLER_T    *controller,
   SCI_BASE_REMOTE_DEVICE_T *remote_device,
   SCI_BASE_REQUEST_T       *io_request,
   U16                       task_tag
)
{
   SCIC_SDS_CONTROLLER_T    *this_controller = (SCIC_SDS_CONTROLLER_T *)
                                               controller;
   SCIC_SDS_REQUEST_T       *the_request     = (SCIC_SDS_REQUEST_T *)
                                               io_request;
   SCIC_SDS_REMOTE_DEVICE_T *the_device      = (SCIC_SDS_REMOTE_DEVICE_T *)
                                               remote_device;
   SCI_STATUS                status;

   status = scic_sds_remote_device_start_task(
               this_controller, the_device, the_request
            );

   if (status == SCI_SUCCESS)
   {
      this_controller->io_request_table[
         scic_sds_io_tag_get_index(the_request->io_tag)] = the_request;

      scic_sds_controller_post_request(
         this_controller,
         scic_sds_request_get_post_context(the_request)
      );
   }
   else if (status == SCI_FAILURE_RESET_DEVICE_PARTIAL_SUCCESS)
   {
      this_controller->io_request_table[
         scic_sds_io_tag_get_index(the_request->io_tag)] = the_request;

      //We will let framework know this task request started successfully,
      //although core is still woring on starting the request (to post tc when
      //RNC is resumed.)
      status = SCI_SUCCESS;
   }
   return status;
}