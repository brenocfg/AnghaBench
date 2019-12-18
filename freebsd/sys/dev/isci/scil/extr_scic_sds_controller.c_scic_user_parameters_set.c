#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t U16 ;
struct TYPE_9__ {scalar_t__ current_state_id; } ;
struct TYPE_10__ {TYPE_1__ state_machine; } ;
struct TYPE_14__ {int /*<<< orphan*/  user_parameters; TYPE_2__ parent; } ;
struct TYPE_12__ {scalar_t__ stp_inactivity_timeout; scalar_t__ ssp_inactivity_timeout; scalar_t__ stp_max_occupancy_timeout; scalar_t__ ssp_max_occupancy_timeout; scalar_t__ no_outbound_task_timeout; TYPE_3__* phys; } ;
struct TYPE_13__ {TYPE_4__ sds1; } ;
struct TYPE_11__ {scalar_t__ max_speed_generation; int in_connection_align_insertion_frequency; scalar_t__ align_insertion_frequency; scalar_t__ notify_enable_spin_up_insertion_frequency; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  scalar_t__ SCI_CONTROLLER_HANDLE_T ;
typedef  TYPE_5__ SCIC_USER_PARAMETERS_T ;
typedef  TYPE_6__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 scalar_t__ SCIC_SDS_PARM_MAX_SPEED ; 
 scalar_t__ SCIC_SDS_PARM_NO_SPEED ; 
 scalar_t__ SCI_BASE_CONTROLLER_STATE_INITIALIZED ; 
 scalar_t__ SCI_BASE_CONTROLLER_STATE_INITIALIZING ; 
 scalar_t__ SCI_BASE_CONTROLLER_STATE_RESET ; 
 int /*<<< orphan*/  SCI_FAILURE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  SCI_FAILURE_INVALID_STATE ; 
 size_t SCI_MAX_PHYS ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_5__*,int) ; 

SCI_STATUS scic_user_parameters_set(
   SCI_CONTROLLER_HANDLE_T   controller,
   SCIC_USER_PARAMETERS_T  * scic_parms
)
{
   SCIC_SDS_CONTROLLER_T * this_controller = (SCIC_SDS_CONTROLLER_T*)controller;

   if (
         (this_controller->parent.state_machine.current_state_id
          == SCI_BASE_CONTROLLER_STATE_RESET)
      || (this_controller->parent.state_machine.current_state_id
          == SCI_BASE_CONTROLLER_STATE_INITIALIZING)
      || (this_controller->parent.state_machine.current_state_id
          == SCI_BASE_CONTROLLER_STATE_INITIALIZED)
      )
   {
      U16  index;

      // Validate the user parameters.  If they are not legal, then
      // return a failure.
      for (index = 0; index < SCI_MAX_PHYS; index++)
      {
         if (!
               (  scic_parms->sds1.phys[index].max_speed_generation
                  <= SCIC_SDS_PARM_MAX_SPEED
               && scic_parms->sds1.phys[index].max_speed_generation
                  > SCIC_SDS_PARM_NO_SPEED
               )
            )
            return SCI_FAILURE_INVALID_PARAMETER_VALUE;

         if (
               (scic_parms->sds1.phys[index].in_connection_align_insertion_frequency < 3) ||
               (scic_parms->sds1.phys[index].align_insertion_frequency == 0) ||
               (scic_parms->sds1.phys[index].notify_enable_spin_up_insertion_frequency == 0)
            )
         {
            return SCI_FAILURE_INVALID_PARAMETER_VALUE;
         }
      }

      if (
            (scic_parms->sds1.stp_inactivity_timeout == 0) ||
            (scic_parms->sds1.ssp_inactivity_timeout == 0) ||
            (scic_parms->sds1.stp_max_occupancy_timeout == 0) ||
            (scic_parms->sds1.ssp_max_occupancy_timeout == 0) ||
            (scic_parms->sds1.no_outbound_task_timeout == 0)
         )
      {
         return SCI_FAILURE_INVALID_PARAMETER_VALUE;
      }

      memcpy(
         (&this_controller->user_parameters), scic_parms, sizeof(*scic_parms));

      return SCI_SUCCESS;
   }

   return SCI_FAILURE_INVALID_STATE;
}