#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  core_object; } ;
struct TYPE_9__ {int /*<<< orphan*/ * list_head; } ;
struct TYPE_12__ {TYPE_6__* controller; TYPE_1__ request_list; } ;
struct TYPE_11__ {int /*<<< orphan*/  core_object; TYPE_4__* domain; } ;
struct TYPE_10__ {scalar_t__ is_waiting_for_abort_task_set; int /*<<< orphan*/  core_object; TYPE_3__* device; } ;
typedef  scalar_t__ SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_FAST_LIST_ELEMENT_T ;
typedef  int /*<<< orphan*/  SCIF_SAS_TASK_REQUEST_T ;
typedef  TYPE_2__ SCIF_SAS_REQUEST_T ;
typedef  TYPE_3__ SCIF_SAS_REMOTE_DEVICE_T ;
typedef  TYPE_4__ SCIF_SAS_DOMAIN_T ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ SCI_FAILURE_INVALID_STATE ; 
 int /*<<< orphan*/  SCI_IO_FAILURE_TERMINATED ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/ * sci_fast_list_get_next (int /*<<< orphan*/ *) ; 
 scalar_t__ sci_fast_list_get_object (int /*<<< orphan*/ *) ; 
 scalar_t__ scic_controller_terminate_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_cb_io_request_complete (TYPE_6__*,TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 

void scif_sas_stp_task_request_abort_task_set_failure_handler(
   SCIF_SAS_REMOTE_DEVICE_T * fw_device,
   SCIF_SAS_TASK_REQUEST_T  * fw_task
)
{
#if !defined(DISABLE_SATI_TASK_MANAGEMENT)
   SCIF_SAS_DOMAIN_T         * fw_domain = fw_device->domain;
   SCI_FAST_LIST_ELEMENT_T   * pending_request_element;
   SCIF_SAS_REQUEST_T        * pending_request = NULL;

   pending_request_element = fw_domain->request_list.list_head;

   // Cycle through the list of IO requests. search all the
   // outstanding IOs with "waiting for abort task set" flag,
   // completes them now.
   while (pending_request_element != NULL)
   {
      pending_request =
         (SCIF_SAS_REQUEST_T*) sci_fast_list_get_object(pending_request_element);

      // The current element may be deleted from the list because of
      // IO completion so advance to the next element early
      pending_request_element = sci_fast_list_get_next(pending_request_element);

      if ( pending_request->device == fw_device
           && pending_request->is_waiting_for_abort_task_set == TRUE )
      {
         //In case the pending_request is still in the middle of aborting.
         //abort it again to the core.
         SCI_STATUS abort_status;

         //Reset the flag now since we are process the read log ext command now.
         pending_request->is_waiting_for_abort_task_set = FALSE;

         abort_status = scic_controller_terminate_request(
                           fw_domain->controller->core_object,
                           fw_device->core_object,
                           pending_request->core_object
                        );

         if (abort_status == SCI_FAILURE_INVALID_STATE)
         {
            //the request must have not be in aborting state anymore, complete it now.
            scif_cb_io_request_complete(
               fw_domain->controller,
               fw_device,
               pending_request,
               SCI_IO_FAILURE_TERMINATED
            );
         }
         //otherwise, the abort succeeded. Since the waiting flag is cleared,
         //the pending request will be completed later.
      }
   }
#endif //#if !defined(DISABLE_SATI_TASK_MANAGEMENT)
}