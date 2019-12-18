#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ current_state_id; } ;
struct TYPE_5__ {TYPE_2__ state_machine; } ;
struct TYPE_7__ {int /*<<< orphan*/  core_object; void* internal_request_entries; TYPE_1__ parent; } ;
typedef  scalar_t__ SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_CONTROLLER_MODE ;
typedef  scalar_t__ SCI_CONTROLLER_HANDLE_T ;
typedef  TYPE_3__ SCIF_SAS_CONTROLLER_T ;

/* Variables and functions */
 void* MIN (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIF_SAS_MAX_INTERNAL_REQUEST_COUNT ; 
 int /*<<< orphan*/  SCIF_SAS_MIN_INTERNAL_REQUEST_COUNT ; 
 scalar_t__ SCI_BASE_CONTROLLER_STATE_INITIALIZED ; 
 scalar_t__ SCI_BASE_CONTROLLER_STATE_INITIALIZING ; 
 scalar_t__ SCI_FAILURE_INVALID_PARAMETER_VALUE ; 
 scalar_t__ SCI_FAILURE_INVALID_STATE ; 
#define  SCI_MODE_SIZE 129 
#define  SCI_MODE_SPEED 128 
 scalar_t__ SCI_SUCCESS ; 
 scalar_t__ scic_controller_set_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_sas_controller_build_mdl (TYPE_3__*) ; 

SCI_STATUS scif_controller_set_mode(
   SCI_CONTROLLER_HANDLE_T   controller,
   SCI_CONTROLLER_MODE       mode
)
{
   SCIF_SAS_CONTROLLER_T * fw_controller = (SCIF_SAS_CONTROLLER_T*) controller;
   SCI_STATUS              status          = SCI_SUCCESS;

   if (
         (fw_controller->parent.state_machine.current_state_id
          == SCI_BASE_CONTROLLER_STATE_INITIALIZING)
      || (fw_controller->parent.state_machine.current_state_id
          == SCI_BASE_CONTROLLER_STATE_INITIALIZED)
      )
   {
      switch (mode)
      {
      case SCI_MODE_SPEED:
         fw_controller->internal_request_entries =
            MIN(fw_controller->internal_request_entries, SCIF_SAS_MAX_INTERNAL_REQUEST_COUNT);
         scif_sas_controller_build_mdl(fw_controller);
      break;

      case SCI_MODE_SIZE:
         fw_controller->internal_request_entries =
            MIN(fw_controller->internal_request_entries, SCIF_SAS_MIN_INTERNAL_REQUEST_COUNT);
         scif_sas_controller_build_mdl(fw_controller);
      break;

      default:
         status = SCI_FAILURE_INVALID_PARAMETER_VALUE;
      break;
      }
   }
   else
      status = SCI_FAILURE_INVALID_STATE;

   if (status != SCI_SUCCESS)
   {
      return status;
   }
   else
   {
      // Currently, the framework doesn't change any configurations for
      // speed or size modes.  Default to speed mode basically.
      return scic_controller_set_mode(fw_controller->core_object, mode);
   }
}