#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_4__* device; TYPE_1__* terminate_requestor; } ;
struct TYPE_11__ {int /*<<< orphan*/  core_object; TYPE_3__* domain; } ;
struct TYPE_10__ {TYPE_2__* controller; } ;
struct TYPE_9__ {int /*<<< orphan*/  core_object; } ;
struct TYPE_8__ {int /*<<< orphan*/  affected_request_count; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_IO_REQUEST_HANDLE_T ;
typedef  TYPE_5__ SCIF_SAS_REQUEST_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_LOG_OBJECT_TASK_MANAGEMENT ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_5__*) ; 
 int /*<<< orphan*/  scic_controller_terminate_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

SCI_STATUS scif_sas_request_terminate_start(
   SCIF_SAS_REQUEST_T      * fw_request,
   SCI_IO_REQUEST_HANDLE_T   core_request
)
{
   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_request),
      SCIF_LOG_OBJECT_TASK_MANAGEMENT,
      "scif_sas_request_terminate_start(0x%x) enter\n",
      fw_request
   ));

   // Only increment the affected request count if this request is being
   // terminated at the behest of a task management request.
   if (fw_request->terminate_requestor != NULL)
      fw_request->terminate_requestor->affected_request_count++;

   return scic_controller_terminate_request(
             fw_request->device->domain->controller->core_object,
             fw_request->device->core_object,
             core_request
          );
}