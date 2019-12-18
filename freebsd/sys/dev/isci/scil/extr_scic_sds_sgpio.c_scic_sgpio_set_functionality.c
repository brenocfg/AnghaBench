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
typedef  int /*<<< orphan*/  U32 ;
typedef  scalar_t__ SCI_CONTROLLER_HANDLE_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_CONTROLLER_T ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DISABLE_SGPIO_FUNCTIONALITY ; 
 int /*<<< orphan*/  ENABLE_SGPIO_FUNCTIONALITY ; 
 int /*<<< orphan*/  interface_control ; 
 int /*<<< orphan*/  scu_sgpio_peg0_register_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void scic_sgpio_set_functionality(
   SCI_CONTROLLER_HANDLE_T controller,
   BOOL sgpio_mode
)
{
   U32 value = DISABLE_SGPIO_FUNCTIONALITY;
   SCIC_SDS_CONTROLLER_T * core_controller = (SCIC_SDS_CONTROLLER_T *) controller;

   if(sgpio_mode)
   {
      value = ENABLE_SGPIO_FUNCTIONALITY;
   }

   scu_sgpio_peg0_register_write(
      core_controller, interface_control, value);
}