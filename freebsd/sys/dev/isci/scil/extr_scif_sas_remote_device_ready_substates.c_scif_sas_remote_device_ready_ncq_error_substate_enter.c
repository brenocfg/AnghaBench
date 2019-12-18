#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * list_head; } ;
struct TYPE_14__ {TYPE_1__ request_list; int /*<<< orphan*/ * controller; } ;
struct TYPE_13__ {TYPE_5__* domain; } ;
struct TYPE_12__ {int /*<<< orphan*/  is_waiting_for_abort_task_set; TYPE_4__* device; } ;
struct TYPE_11__ {TYPE_3__ parent; } ;
typedef  int /*<<< orphan*/  SCI_TASK_REQUEST_HANDLE_T ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_FAST_LIST_ELEMENT_T ;
typedef  int /*<<< orphan*/  SCI_BASE_OBJECT_T ;
typedef  TYPE_2__ SCIF_SAS_TASK_REQUEST_T ;
typedef  TYPE_3__ SCIF_SAS_REQUEST_T ;
typedef  TYPE_4__ SCIF_SAS_REMOTE_DEVICE_T ;
typedef  TYPE_5__ SCIF_SAS_DOMAIN_T ;
typedef  int /*<<< orphan*/  SCIF_SAS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIF_SAS_REMOTE_DEVICE_READY_SUBSTATE_NCQ_ERROR ; 
 int /*<<< orphan*/  SCI_CONTROLLER_INVALID_IO_TAG ; 
 int /*<<< orphan*/  SCI_SAS_ABORT_TASK_SET ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  SET_STATE_HANDLER (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * sci_fast_list_get_next (int /*<<< orphan*/ *) ; 
 scalar_t__ sci_fast_list_get_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scif_controller_start_task (int /*<<< orphan*/ *,TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 void* scif_sas_controller_allocate_internal_request (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scif_sas_internal_task_request_construct (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_sas_remote_device_ready_substate_handler_table ; 

__attribute__((used)) static
void scif_sas_remote_device_ready_ncq_error_substate_enter(
   SCI_BASE_OBJECT_T *object
)
{
   SCIF_SAS_REMOTE_DEVICE_T         * fw_device = (SCIF_SAS_REMOTE_DEVICE_T *)object;
   SCI_STATUS                         status = SCI_SUCCESS;
   SCI_TASK_REQUEST_HANDLE_T          handle;
   SCIF_SAS_CONTROLLER_T            * fw_controller = fw_device->domain->controller;
   SCIF_SAS_TASK_REQUEST_T          * fw_task_request;
   SCIF_SAS_REQUEST_T               * fw_request;
   void                             * internal_task_memory;
   SCIF_SAS_DOMAIN_T                * fw_domain = fw_device->domain;
   SCI_FAST_LIST_ELEMENT_T          * pending_request_element;
   SCIF_SAS_REQUEST_T               * pending_request = NULL;

   SET_STATE_HANDLER(
      fw_device,
      scif_sas_remote_device_ready_substate_handler_table,
      SCIF_SAS_REMOTE_DEVICE_READY_SUBSTATE_NCQ_ERROR
   );

   internal_task_memory = scif_sas_controller_allocate_internal_request(fw_controller);
   ASSERT(internal_task_memory != NULL);

   fw_task_request = (SCIF_SAS_TASK_REQUEST_T*)internal_task_memory;

   fw_request = &fw_task_request->parent;

   //construct the scif io request
   status = scif_sas_internal_task_request_construct(
      fw_controller,
      fw_device,
      SCI_CONTROLLER_INVALID_IO_TAG,
      (void *)fw_task_request,
      &handle,
      SCI_SAS_ABORT_TASK_SET
   );

   pending_request_element = fw_domain->request_list.list_head;

   // Cycle through the fast list of IO requests.  Mark each request
   //  pending to this remote device so that they are not completed
   //  to the operating system when the request is terminated, but
   //  rather when the abort task set completes.
   while (pending_request_element != NULL)
   {
      pending_request =
         (SCIF_SAS_REQUEST_T*) sci_fast_list_get_object(pending_request_element);

      // The current element may be deleted from the list because of
      // IO completion so advance to the next element early
      pending_request_element = sci_fast_list_get_next(pending_request_element);

      if (pending_request->device == fw_device)
      {
         pending_request->is_waiting_for_abort_task_set = TRUE;
      }
   }

   scif_controller_start_task(
      fw_controller,
      fw_device,
      fw_request,
      SCI_CONTROLLER_INVALID_IO_TAG
   );
}