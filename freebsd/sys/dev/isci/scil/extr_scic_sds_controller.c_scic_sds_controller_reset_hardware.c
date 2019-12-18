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
typedef  int /*<<< orphan*/  SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCU_UFQGP_WRITE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SMU_CQGR_WRITE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SMU_SMUSRCR_WRITE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  scic_cb_stall_execution (int) ; 
 int /*<<< orphan*/  scic_controller_disable_interrupts (int /*<<< orphan*/ *) ; 

void scic_sds_controller_reset_hardware(
   SCIC_SDS_CONTROLLER_T * this_controller
)
{
   // Disable interrupts so we dont take any spurious interrupts
   scic_controller_disable_interrupts(this_controller);

   // Reset the SCU
   SMU_SMUSRCR_WRITE(this_controller, 0xFFFFFFFF);

   // Delay for 1ms to before clearing the CQP and UFQPR.
   scic_cb_stall_execution(1000);

   // The write to the CQGR clears the CQP
   SMU_CQGR_WRITE(this_controller, 0x00000000);

   // The write to the UFQGP clears the UFQPR
   SCU_UFQGP_WRITE(this_controller, 0x00000000);
}