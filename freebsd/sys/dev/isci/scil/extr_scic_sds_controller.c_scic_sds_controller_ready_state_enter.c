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
typedef  int /*<<< orphan*/  SCI_BASE_OBJECT_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  IDLE_ENABLE ; 
 int /*<<< orphan*/  REGCLK_ENABLE ; 
 int /*<<< orphan*/  SCI_BASE_CONTROLLER_STATE_READY ; 
 int SMU_CGUCR_GEN_BIT (int /*<<< orphan*/ ) ; 
 int SMU_CGUCR_READ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SMU_CGUCR_WRITE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TXCLK_ENABLE ; 
 int /*<<< orphan*/  XCLK_ENABLE ; 
 int /*<<< orphan*/  scic_controller_set_interrupt_coalescence (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  scic_sds_controller_set_base_state_handlers (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void scic_sds_controller_ready_state_enter(
   SCI_BASE_OBJECT_T *object
)
{
   U32 clock_gating_unit_value;
   SCIC_SDS_CONTROLLER_T *this_controller;
   this_controller= (SCIC_SDS_CONTROLLER_T *)object;

   scic_sds_controller_set_base_state_handlers(
      this_controller, SCI_BASE_CONTROLLER_STATE_READY);

   /**
    * enable clock gating for power control of the scu unit
    */
   clock_gating_unit_value = SMU_CGUCR_READ(this_controller);

   clock_gating_unit_value &= ~( SMU_CGUCR_GEN_BIT(REGCLK_ENABLE)
                               | SMU_CGUCR_GEN_BIT(TXCLK_ENABLE)
                               | SMU_CGUCR_GEN_BIT(XCLK_ENABLE) );
   clock_gating_unit_value |= SMU_CGUCR_GEN_BIT(IDLE_ENABLE);

   SMU_CGUCR_WRITE(this_controller, clock_gating_unit_value);

   //set the default interrupt coalescence number and timeout value.
   scic_controller_set_interrupt_coalescence(
      this_controller, 0x10, 250);
}