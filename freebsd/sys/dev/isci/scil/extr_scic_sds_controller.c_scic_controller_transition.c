#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t U8 ;
struct TYPE_8__ {scalar_t__ current_state_id; } ;
struct TYPE_9__ {TYPE_2__ state_machine; } ;
struct TYPE_10__ {int /*<<< orphan*/  restrict_completions; TYPE_1__* port_table; TYPE_3__ parent; } ;
struct TYPE_7__ {scalar_t__ started_request_count; } ;
typedef  scalar_t__ SCI_STATUS ;
typedef  scalar_t__ SCI_CONTROLLER_HANDLE_T ;
typedef  TYPE_4__ SCIC_SDS_CONTROLLER_T ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_LOG_OBJECT_CONTROLLER ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ SCI_BASE_CONTROLLER_STATE_READY ; 
 scalar_t__ SCI_FAILURE_INVALID_STATE ; 
 size_t SCI_MAX_PORTS ; 
 scalar_t__ SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_base_object_get_logger (scalar_t__) ; 
 int /*<<< orphan*/  scic_controller_resume (scalar_t__) ; 
 int /*<<< orphan*/  scic_controller_suspend (scalar_t__) ; 
 int /*<<< orphan*/  scic_sds_controller_ram_initialization (TYPE_4__*) ; 
 scalar_t__ scic_sds_controller_validate_memory_descriptor_table (TYPE_4__*) ; 

SCI_STATUS scic_controller_transition(
   SCI_CONTROLLER_HANDLE_T   controller,
   BOOL                      restrict_completions
)
{
   SCI_STATUS              result = SCI_FAILURE_INVALID_STATE;
   SCIC_SDS_CONTROLLER_T * this_controller = (SCIC_SDS_CONTROLLER_T*)controller;
   U8                      index;

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(controller),
      SCIC_LOG_OBJECT_CONTROLLER,
      "scic_controller_transition(0x%x) enter\n",
      controller
   ));

   if (this_controller->parent.state_machine.current_state_id
       == SCI_BASE_CONTROLLER_STATE_READY)
   {
      // Ensure that there are no outstanding IO operations at this
      // time.
      for (index = 0; index < SCI_MAX_PORTS; index++)
      {
         if (this_controller->port_table[index].started_request_count != 0)
            return result;
      }

      scic_controller_suspend(controller);

      // Loop through the memory descriptor list and reprogram
      // the silicon memory registers accordingly.
      result = scic_sds_controller_validate_memory_descriptor_table(
                  this_controller);
      if (result == SCI_SUCCESS)
      {
         scic_sds_controller_ram_initialization(this_controller);
         this_controller->restrict_completions = restrict_completions;
      }

      scic_controller_resume(controller);
   }

   return result;
}