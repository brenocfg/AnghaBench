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
struct TYPE_4__ {int /*<<< orphan*/  saved_interrupt_coalesce_timeout; int /*<<< orphan*/  saved_interrupt_coalesce_number; int /*<<< orphan*/  core_object; } ;
typedef  TYPE_1__ SCIF_SAS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  scic_controller_set_interrupt_coalescence (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_sas_controller_is_overriding_interrupt_coalescence (TYPE_1__*) ; 

void scif_sas_controller_restore_interrupt_coalescence(
   SCIF_SAS_CONTROLLER_T * fw_controller
)
{
   if ( !scif_sas_controller_is_overriding_interrupt_coalescence(fw_controller))
      scic_controller_set_interrupt_coalescence(
         fw_controller->core_object,
         fw_controller->saved_interrupt_coalesce_number,
         fw_controller->saved_interrupt_coalesce_timeout
      );
}