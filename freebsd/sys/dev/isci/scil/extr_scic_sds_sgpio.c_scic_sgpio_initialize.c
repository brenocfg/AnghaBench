#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  SCI_CONTROLLER_HANDLE_T ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  scic_sgpio_set_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sgpio_set_to_hardware_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sgpio_set_vendor_code (int /*<<< orphan*/ ,int) ; 

void scic_sgpio_initialize(
   SCI_CONTROLLER_HANDLE_T controller
)
{
   scic_sgpio_set_functionality(controller, TRUE);
   scic_sgpio_set_to_hardware_control(controller, FALSE);
   scic_sgpio_set_vendor_code(controller, 0x00);
}