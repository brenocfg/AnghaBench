#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * terminate_requestor; } ;
typedef  TYPE_1__ SCIF_SAS_REQUEST_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_LOG_OBJECT_TASK_MANAGEMENT ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_1__*) ; 
 int /*<<< orphan*/  scif_sas_task_request_operation_complete (int /*<<< orphan*/ *) ; 

void scif_sas_request_terminate_complete(
   SCIF_SAS_REQUEST_T * fw_request
)
{
   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_request),
      SCIF_LOG_OBJECT_TASK_MANAGEMENT,
      "scif_sas_request_terminate_complete(0x%x) enter\n",
      fw_request
   ));

   // For requests that were terminated due to a task management request,
   // check to see if the task management request has completed.
   if (fw_request->terminate_requestor != NULL)
      scif_sas_task_request_operation_complete(fw_request->terminate_requestor);
}