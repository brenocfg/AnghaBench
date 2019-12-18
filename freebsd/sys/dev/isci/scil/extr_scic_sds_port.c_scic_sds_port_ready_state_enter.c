#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ previous_state_id; } ;
struct TYPE_11__ {TYPE_1__ state_machine; } ;
struct TYPE_12__ {TYPE_2__ parent; } ;
typedef  int /*<<< orphan*/  SCI_BASE_OBJECT_T ;
typedef  TYPE_3__ SCIC_SDS_PORT_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_PORT_NOT_READY_NO_ACTIVE_PHYS ; 
 int /*<<< orphan*/  SCI_BASE_PORT_STATE_READY ; 
 scalar_t__ SCI_BASE_PORT_STATE_RESETTING ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_base_state_machine_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_cb_port_hard_reset_complete (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_cb_port_not_ready (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_port_get_controller (TYPE_3__*) ; 
 int /*<<< orphan*/  scic_sds_port_get_ready_substate_machine (TYPE_3__*) ; 
 int /*<<< orphan*/  scic_sds_port_post_dummy_remote_node (TYPE_3__*) ; 
 int /*<<< orphan*/  scic_sds_port_set_base_state_handlers (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void scic_sds_port_ready_state_enter(
   SCI_BASE_OBJECT_T *object
)
{
   SCIC_SDS_PORT_T *this_port;
   this_port = (SCIC_SDS_PORT_T *)object;

   // Put the ready state handlers in place though they will not be there long
   scic_sds_port_set_base_state_handlers(
      this_port, SCI_BASE_PORT_STATE_READY
   );

   if (
          SCI_BASE_PORT_STATE_RESETTING
      == this_port->parent.state_machine.previous_state_id
      )
   {
      scic_cb_port_hard_reset_complete(
         scic_sds_port_get_controller(this_port),
         this_port,
         SCI_SUCCESS
      );
   }
   else
   {
      // Notify the caller that the port is not yet ready
      scic_cb_port_not_ready(
         scic_sds_port_get_controller(this_port),
         this_port,
         SCIC_PORT_NOT_READY_NO_ACTIVE_PHYS
      );
   }

   // Post and suspend the dummy remote node context for this
   // port.
   scic_sds_port_post_dummy_remote_node(this_port);

   // Start the ready substate machine
   sci_base_state_machine_start(
      scic_sds_port_get_ready_substate_machine(this_port)
   );
}