#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_2__ {int /*<<< orphan*/  core_object; } ;
typedef  scalar_t__ SCI_CONTROLLER_HANDLE_T ;
typedef  TYPE_1__ SCIF_SAS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  scic_controller_get_interrupt_coalescence (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void scif_controller_get_interrupt_coalescence(
   SCI_CONTROLLER_HANDLE_T controller,
   U32                   * coalesce_number,
   U32                   * coalesce_timeout
)
{
   SCIF_SAS_CONTROLLER_T * scif_controller = (SCIF_SAS_CONTROLLER_T * )controller;

   scic_controller_get_interrupt_coalescence(
      scif_controller->core_object, coalesce_number, coalesce_timeout);
}