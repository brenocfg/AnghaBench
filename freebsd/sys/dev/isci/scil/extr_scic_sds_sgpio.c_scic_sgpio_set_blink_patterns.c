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
typedef  int U8 ;
typedef  int U32 ;
typedef  scalar_t__ SCI_CONTROLLER_HANDLE_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  blink_rate ; 
 int /*<<< orphan*/  scu_sgpio_peg0_register_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void scic_sgpio_set_blink_patterns(
   SCI_CONTROLLER_HANDLE_T controller,
   U8 pattern_a_low,
   U8 pattern_a_high,
   U8 pattern_b_low,
   U8 pattern_b_high
)
{
   U32 value;
   SCIC_SDS_CONTROLLER_T * core_controller = (SCIC_SDS_CONTROLLER_T *) controller;

   value = (pattern_b_high << 12) + (pattern_b_low << 8) + (pattern_a_high << 4) + pattern_a_low;

   scu_sgpio_peg0_register_write(
      core_controller, blink_rate, value);
}