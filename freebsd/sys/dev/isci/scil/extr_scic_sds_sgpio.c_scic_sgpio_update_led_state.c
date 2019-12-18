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
typedef  int U32 ;
typedef  scalar_t__ SCI_CONTROLLER_HANDLE_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_CONTROLLER_T ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int SGODSR_ACTIVITY_LED_SHIFT ; 
 int SGODSR_ERROR_LED_SHIFT ; 
 int SGODSR_INVERT_BIT ; 
 int SGODSR_LOCATE_LED_SHIFT ; 
 int /*<<< orphan*/  scic_sgpio_write_SGODSR_register (int /*<<< orphan*/ *,int,int) ; 

void scic_sgpio_update_led_state(
   SCI_CONTROLLER_HANDLE_T controller,
   U32 phy_mask,
   BOOL error,
   BOOL locate,
   BOOL activity
)
{
   U32 output_value;

   SCIC_SDS_CONTROLLER_T * core_controller = (SCIC_SDS_CONTROLLER_T *) controller;

   // Start with all LEDs turned on
   output_value = 0x00000000;

   if(!error)
   {  //turn off error LED
      output_value |= SGODSR_INVERT_BIT <<  SGODSR_ERROR_LED_SHIFT;
   }
   if(!locate)
   {  //turn off locate LED
      output_value |= SGODSR_INVERT_BIT <<  SGODSR_LOCATE_LED_SHIFT;
   }
   if(!activity)
   {  //turn off activity LED
      output_value |= SGODSR_INVERT_BIT <<  SGODSR_ACTIVITY_LED_SHIFT;
   }

   scic_sgpio_write_SGODSR_register(core_controller, phy_mask, output_value);
}