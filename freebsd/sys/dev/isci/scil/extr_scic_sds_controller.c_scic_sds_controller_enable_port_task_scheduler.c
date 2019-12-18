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
typedef  int /*<<< orphan*/  SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  ETM_ENABLE ; 
 int /*<<< orphan*/  PTSG_ENABLE ; 
 int SCU_PTSGCR_GEN_BIT (int /*<<< orphan*/ ) ; 
 int SCU_PTSGCR_READ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCU_PTSGCR_WRITE (int /*<<< orphan*/ *,int) ; 

void scic_sds_controller_enable_port_task_scheduler(
   SCIC_SDS_CONTROLLER_T *this_controller
)
{
   U32 port_task_scheduler_value;

   port_task_scheduler_value = SCU_PTSGCR_READ(this_controller);

   port_task_scheduler_value |=
      (SCU_PTSGCR_GEN_BIT(ETM_ENABLE) | SCU_PTSGCR_GEN_BIT(PTSG_ENABLE));

   SCU_PTSGCR_WRITE(this_controller, port_task_scheduler_value);
}