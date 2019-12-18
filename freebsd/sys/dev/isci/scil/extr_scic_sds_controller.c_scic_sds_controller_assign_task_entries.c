#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int U32 ;
struct TYPE_5__ {scalar_t__ task_context_entries; } ;
typedef  TYPE_1__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  ENDING ; 
 int /*<<< orphan*/  RANGE_CHECK_ENABLE ; 
 int SMU_TCA_GEN_BIT (int /*<<< orphan*/ ) ; 
 int SMU_TCA_GEN_VAL (int /*<<< orphan*/ ,scalar_t__) ; 
 int SMU_TCA_READ (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMU_TCA_WRITE (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STARTING ; 

void scic_sds_controller_assign_task_entries(
   SCIC_SDS_CONTROLLER_T *this_controller
)
{
   U32 task_assignment;

   // Assign all the TCs to function 0
   // TODO: Do we actually need to read this register to write it back?
   task_assignment = SMU_TCA_READ(this_controller, 0);

   task_assignment =
      (
          task_assignment
        | (SMU_TCA_GEN_VAL(STARTING, 0))
        | (SMU_TCA_GEN_VAL(ENDING,  this_controller->task_context_entries - 1))
        | (SMU_TCA_GEN_BIT(RANGE_CHECK_ENABLE))
      );

   SMU_TCA_WRITE(this_controller, 0, task_assignment);
}