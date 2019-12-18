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
typedef  int /*<<< orphan*/  U8 ;
typedef  scalar_t__ SCI_CONTROLLER_HANDLE_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  scu_sgpio_peg0_register_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vendor_specific_code ; 

void scic_sgpio_set_vendor_code(
   SCI_CONTROLLER_HANDLE_T controller,
   U8 vendor_specific_sequence
)
{
   SCIC_SDS_CONTROLLER_T * core_controller = (SCIC_SDS_CONTROLLER_T *) controller;

   scu_sgpio_peg0_register_write(
      core_controller, vendor_specific_code, vendor_specific_sequence);
}