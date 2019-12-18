#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ previous_state_id; } ;
struct TYPE_7__ {TYPE_1__ state_machine; } ;
struct TYPE_8__ {TYPE_2__ parent; } ;
typedef  int /*<<< orphan*/  SCI_BASE_OBJECT_T ;
typedef  TYPE_3__ SCIC_SDS_PORT_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_BASE_PORT_STATE_STOPPED ; 
 scalar_t__ SCI_BASE_PORT_STATE_STOPPING ; 
 int /*<<< orphan*/  scic_sds_port_disable_port_task_scheduler (TYPE_3__*) ; 
 int /*<<< orphan*/  scic_sds_port_set_base_state_handlers (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void scic_sds_port_stopped_state_enter(
   SCI_BASE_OBJECT_T *object
)
{
   SCIC_SDS_PORT_T *this_port;
   this_port = (SCIC_SDS_PORT_T *)object;

   scic_sds_port_set_base_state_handlers(
      this_port, SCI_BASE_PORT_STATE_STOPPED
   );

   if (
         SCI_BASE_PORT_STATE_STOPPING
      == this_port->parent.state_machine.previous_state_id
      )
   {
      // If we enter this state becasuse of a request to stop
      // the port then we want to disable the hardwares port
      // task scheduler.
      scic_sds_port_disable_port_task_scheduler(this_port);
   }
}