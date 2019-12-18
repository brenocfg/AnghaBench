#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  list_element; void* is_waiting_for_abort_task_set; void* is_high_priority; int /*<<< orphan*/ * protocol_complete_handler; int /*<<< orphan*/ * terminate_requestor; scalar_t__ lun; void* is_internal; int /*<<< orphan*/ * device; int /*<<< orphan*/  parent; } ;
typedef  int /*<<< orphan*/  SCI_BASE_STATE_T ;
typedef  int /*<<< orphan*/  SCI_BASE_LOGGER_T ;
typedef  TYPE_1__ SCIF_SAS_REQUEST_T ;
typedef  int /*<<< orphan*/  SCIF_SAS_REMOTE_DEVICE_T ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  SCIF_LOG_OBJECT_TASK_MANAGEMENT ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_1__*) ; 
 int /*<<< orphan*/  sci_base_request_construct (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sci_fast_list_element_init (TYPE_1__*,int /*<<< orphan*/ *) ; 

void scif_sas_request_construct(
   SCIF_SAS_REQUEST_T       * fw_request,
   SCIF_SAS_REMOTE_DEVICE_T * fw_device,
   SCI_BASE_LOGGER_T        * logger,
   SCI_BASE_STATE_T         * state_table
)
{
   sci_base_request_construct(&fw_request->parent, logger, state_table);

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_request),
      SCIF_LOG_OBJECT_TASK_MANAGEMENT,
      "scif_sas_request_construct(0x%x, 0x%x, 0x%x, 0x%x) enter\n",
      fw_request, fw_device, logger, state_table
   ));

   fw_request->device                    = fw_device;
   fw_request->is_internal               = FALSE;
   fw_request->lun                       = 0;
   fw_request->terminate_requestor       = NULL;
   fw_request->protocol_complete_handler = NULL;
   fw_request->is_high_priority          = FALSE;
   fw_request->is_waiting_for_abort_task_set = FALSE;

   sci_fast_list_element_init(fw_request, &fw_request->list_element);
}