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
struct TYPE_2__ {int /*<<< orphan*/  interrupt_coalesce_timeout; int /*<<< orphan*/  interrupt_coalesce_number; } ;
typedef  scalar_t__ SCI_CONTROLLER_HANDLE_T ;
typedef  TYPE_1__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */

void scic_controller_get_interrupt_coalescence(
   SCI_CONTROLLER_HANDLE_T   controller,
   U32                     * coalesce_number,
   U32                     * coalesce_timeout
)
{
   SCIC_SDS_CONTROLLER_T * scic_controller = (SCIC_SDS_CONTROLLER_T *)controller;
   *coalesce_number = scic_controller->interrupt_coalesce_number;
   *coalesce_timeout = scic_controller->interrupt_coalesce_timeout;
}