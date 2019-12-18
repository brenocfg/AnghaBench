#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * list_head; } ;
struct TYPE_11__ {TYPE_1__ request_list; } ;
struct TYPE_10__ {scalar_t__ is_waiting_for_abort_task_set; int /*<<< orphan*/  parent; TYPE_2__* state_handlers; int /*<<< orphan*/ * terminate_requestor; int /*<<< orphan*/ * device; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* abort_handler ) (int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  SCI_FAST_LIST_ELEMENT_T ;
typedef  int /*<<< orphan*/  SCIF_SAS_TASK_REQUEST_T ;
typedef  TYPE_3__ SCIF_SAS_REQUEST_T ;
typedef  int /*<<< orphan*/  SCIF_SAS_REMOTE_DEVICE_T ;
typedef  TYPE_4__ SCIF_SAS_DOMAIN_T ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int SCIF_LOG_OBJECT_DOMAIN ; 
 int SCIF_LOG_OBJECT_TASK_MANAGEMENT ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_4__*) ; 
 int /*<<< orphan*/ * sci_fast_list_get_next (int /*<<< orphan*/ *) ; 
 scalar_t__ sci_fast_list_get_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 

void scif_sas_domain_terminate_requests(
   SCIF_SAS_DOMAIN_T        * fw_domain,
   SCIF_SAS_REMOTE_DEVICE_T * fw_device,
   SCIF_SAS_REQUEST_T       * fw_request,
   SCIF_SAS_TASK_REQUEST_T  * fw_requestor
)
{
   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_domain),
      SCIF_LOG_OBJECT_DOMAIN | SCIF_LOG_OBJECT_TASK_MANAGEMENT,
      "scif_sas_domain_terminate_requests(0x%x, 0x%x, 0x%x, 0x%x) enter\n",
      fw_domain, fw_device, fw_request, fw_requestor
   ));

   if (fw_request != NULL)
   {
      fw_request->terminate_requestor = fw_requestor;
      fw_request->state_handlers->abort_handler(&fw_request->parent);
   }
   else
   {
      SCI_FAST_LIST_ELEMENT_T * element = fw_domain->request_list.list_head;
      SCIF_SAS_REQUEST_T      * request = NULL;

      // Cycle through the fast list of IO requests.  Terminate each
      // outstanding requests that matches the criteria supplied by the
      // caller.
      while (element != NULL)
      {
         request = (SCIF_SAS_REQUEST_T*) sci_fast_list_get_object(element);
         // The current element may be deleted from the list because of
         // IO completion so advance to the next element early
         element = sci_fast_list_get_next(element);

         // Ensure we pass the supplied criteria before terminating the
         // request.
         if (
               (fw_device == NULL)
            || (
                  (request->device == fw_device)
               && (fw_requestor != (SCIF_SAS_TASK_REQUEST_T*) request)
               )
            )
         {
            if (
                  (request->is_waiting_for_abort_task_set == FALSE) ||
                  (request->terminate_requestor == NULL)
               )
            {
               request->terminate_requestor = fw_requestor;
               request->state_handlers->abort_handler(&request->parent);
            }
         }
      }
   }
}