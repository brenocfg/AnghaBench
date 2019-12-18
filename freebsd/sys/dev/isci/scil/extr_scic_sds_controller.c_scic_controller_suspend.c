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
typedef  size_t U8 ;
struct TYPE_5__ {scalar_t__ completion_queue_get; int /*<<< orphan*/ * port_table; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  scalar_t__ SCI_CONTROLLER_HANDLE_T ;
typedef  TYPE_1__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 size_t SCI_MAX_PORTS ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  SCU_UFQGP_WRITE (TYPE_1__*,int) ; 
 int /*<<< orphan*/  SMU_CQGR_WRITE (TYPE_1__*,int) ; 
 int /*<<< orphan*/  SMU_ISR_WRITE (TYPE_1__*,int) ; 
 int /*<<< orphan*/  scic_controller_disable_interrupts (scalar_t__) ; 
 int /*<<< orphan*/  scic_sds_port_suspend_port_task_scheduler (int /*<<< orphan*/ *) ; 

SCI_STATUS scic_controller_suspend(
   SCI_CONTROLLER_HANDLE_T   controller
)
{
   SCIC_SDS_CONTROLLER_T * this_controller = (SCIC_SDS_CONTROLLER_T*)controller;
   U8 index;

   // As a precaution, disable interrupts.  The user is required
   // to re-enable interrupts if so desired after the call.
   scic_controller_disable_interrupts(controller);

   // Stop all the timers
   // Maybe change the states of the objects to avoid processing stuff.


   // Suspend the Ports in order to ensure no unexpected
   // frame reception occurs on the links from the target
   for (index = 0; index < SCI_MAX_PORTS; index++)
      scic_sds_port_suspend_port_task_scheduler(
         &(this_controller->port_table[index]));

   // Disable/Reset the completion queue and unsolicited frame
   // queue.
   SMU_CQGR_WRITE(this_controller, 0x00000000);
   SCU_UFQGP_WRITE(this_controller, 0x00000000);

   // Clear any interrupts that may be pending or may have been generated
   // by setting CQGR and CQPR back to 0
   SMU_ISR_WRITE(this_controller, 0xFFFFFFFF);

   //reset the software get pointer to completion queue.
   this_controller->completion_queue_get = 0;

   return SCI_SUCCESS;
}