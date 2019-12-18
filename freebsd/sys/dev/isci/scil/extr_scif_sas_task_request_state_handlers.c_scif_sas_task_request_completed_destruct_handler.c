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
struct TYPE_5__ {scalar_t__ is_internal; } ;
struct TYPE_4__ {int /*<<< orphan*/  state_machine; int /*<<< orphan*/  state_machine_logger; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  TYPE_1__ SCI_BASE_REQUEST_T ;
typedef  int /*<<< orphan*/  SCIF_SAS_TASK_REQUEST_T ;
typedef  TYPE_2__ SCIF_SAS_REQUEST_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_BASE_REQUEST_STATE_FINAL ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_state_machine_logger_deinitialize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scif_sas_internal_task_request_destruct (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
SCI_STATUS scif_sas_task_request_completed_destruct_handler(
   SCI_BASE_REQUEST_T * task_request
)
{
   SCIF_SAS_REQUEST_T * fw_request = (SCIF_SAS_REQUEST_T *)task_request;

   sci_base_state_machine_change_state(
      &task_request->state_machine, SCI_BASE_REQUEST_STATE_FINAL
   );

   sci_base_state_machine_logger_deinitialize(
      &task_request->state_machine_logger,
      &task_request->state_machine
   );

   if (fw_request->is_internal == TRUE)
   {
      scif_sas_internal_task_request_destruct(
         (SCIF_SAS_TASK_REQUEST_T *)fw_request
      );
   }

   return SCI_SUCCESS;
}