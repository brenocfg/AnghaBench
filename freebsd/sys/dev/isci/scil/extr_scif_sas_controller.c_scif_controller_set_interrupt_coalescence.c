#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ U32 ;
typedef  scalar_t__ U16 ;
struct TYPE_3__ {int /*<<< orphan*/  core_object; scalar_t__ saved_interrupt_coalesce_timeout; scalar_t__ saved_interrupt_coalesce_number; } ;
typedef  scalar_t__ SCI_STATUS ;
typedef  scalar_t__ SCI_CONTROLLER_HANDLE_T ;
typedef  TYPE_1__ SCIF_SAS_CONTROLLER_T ;

/* Variables and functions */
 scalar_t__ SCI_SUCCESS ; 
 int /*<<< orphan*/  scic_controller_get_interrupt_coalescence (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 scalar_t__ scic_controller_set_interrupt_coalescence (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ scif_sas_controller_is_overriding_interrupt_coalescence (TYPE_1__*) ; 

SCI_STATUS scif_controller_set_interrupt_coalescence(
   SCI_CONTROLLER_HANDLE_T controller,
   U32                     coalesce_number,
   U32                     coalesce_timeout
)
{
   SCIF_SAS_CONTROLLER_T * fw_controller = (SCIF_SAS_CONTROLLER_T * )controller;

   ///when framework is in the middle of temporarily overriding the interrupt
   ///coalescence values, user's request of setting interrupt coalescence
   ///will be saved. As soon as the framework done the temporary overriding,
   ///it will serve user's request to set new interrupt coalescence.
   if (scif_sas_controller_is_overriding_interrupt_coalescence(fw_controller))
   {
      U32 curr_coalesce_number;
      U32 curr_coalesce_timeout;
      SCI_STATUS core_status;

      // save current interrupt coalescence info.
      scic_controller_get_interrupt_coalescence (
         fw_controller->core_object, &curr_coalesce_number, &curr_coalesce_timeout);

      //try user's request out in the core, but immediately restore core's
      //current setting.
      core_status = scic_controller_set_interrupt_coalescence(
                       fw_controller->core_object, coalesce_number, coalesce_timeout);

      if ( core_status == SCI_SUCCESS )
      {
         fw_controller->saved_interrupt_coalesce_number = (U16)coalesce_number;
         fw_controller->saved_interrupt_coalesce_timeout = coalesce_timeout;
      }

       //restore current interrupt coalescence.
      scic_controller_set_interrupt_coalescence(
         fw_controller->core_object, curr_coalesce_number, curr_coalesce_timeout);

      return core_status;
   }
   else
   {
      ///If framework is not internally overriding the interrupt coalescence,
      ///serve user's request immediately by passing the reqeust to core.
      return scic_controller_set_interrupt_coalescence(
                fw_controller->core_object, coalesce_number, coalesce_timeout);
   }
}