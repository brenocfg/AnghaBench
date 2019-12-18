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
typedef  int /*<<< orphan*/  SCI_BASE_OBJECT_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_PORT_T ;

/* Variables and functions */
 int /*<<< orphan*/  scic_sds_port_enable_port_task_scheduler (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
void scic_sds_port_stopped_state_exit(
   SCI_BASE_OBJECT_T *object
)
{
   SCIC_SDS_PORT_T *this_port;
   this_port = (SCIC_SDS_PORT_T *)object;

   // Enable and suspend the port task scheduler
   scic_sds_port_enable_port_task_scheduler(this_port);
}