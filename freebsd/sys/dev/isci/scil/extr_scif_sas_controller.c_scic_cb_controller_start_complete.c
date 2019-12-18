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
struct TYPE_4__ {int /*<<< orphan*/  state_machine; } ;
struct TYPE_5__ {TYPE_1__ parent; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_CONTROLLER_HANDLE_T ;
typedef  TYPE_2__ SCIF_SAS_CONTROLLER_T ;

/* Variables and functions */
 int SCIF_LOG_OBJECT_CONTROLLER ; 
 int SCIF_LOG_OBJECT_INITIALIZATION ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCI_BASE_CONTROLLER_STATE_READY ; 
 int /*<<< orphan*/  SCI_FAILURE_TIMEOUT ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_base_object_get_logger (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sci_object_get_association (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_cb_controller_start_complete (TYPE_2__*,int /*<<< orphan*/ ) ; 

void scic_cb_controller_start_complete(
   SCI_CONTROLLER_HANDLE_T  controller,
   SCI_STATUS               completion_status
)
{
   SCIF_SAS_CONTROLLER_T *fw_controller = (SCIF_SAS_CONTROLLER_T*)
                                         sci_object_get_association(controller);

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(controller),
      SCIF_LOG_OBJECT_CONTROLLER | SCIF_LOG_OBJECT_INITIALIZATION,
      "scic_cb_controller_start_complete(0x%x, 0x%x) enter\n",
      controller, completion_status
   ));

   if (completion_status == SCI_SUCCESS
       || completion_status == SCI_FAILURE_TIMEOUT)
   {
      // Even the initialization of the core controller timed out, framework
      // controller should still transit to READY state.
      sci_base_state_machine_change_state(
         &fw_controller->parent.state_machine,
         SCI_BASE_CONTROLLER_STATE_READY
      );
   }

   scif_cb_controller_start_complete(fw_controller, completion_status);
}