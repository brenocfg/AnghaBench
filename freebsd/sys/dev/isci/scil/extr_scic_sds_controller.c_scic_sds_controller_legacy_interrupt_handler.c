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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  SMU_ISR_READ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_controller_standard_interrupt_handler (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
BOOL scic_sds_controller_legacy_interrupt_handler(
   SCI_CONTROLLER_HANDLE_T controller
)
{
   U32                    interrupt_status;
   BOOL                   is_completion_needed;
   SCIC_SDS_CONTROLLER_T *this_controller = (SCIC_SDS_CONTROLLER_T*)controller;

   interrupt_status     = SMU_ISR_READ(this_controller);
   is_completion_needed = scic_sds_controller_standard_interrupt_handler(
                             this_controller, interrupt_status
                          );

   return is_completion_needed;
}