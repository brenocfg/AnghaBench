#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ U32 ;
struct TYPE_5__ {int /*<<< orphan*/  state_machine; } ;
struct TYPE_6__ {TYPE_1__ parent; } ;
typedef  TYPE_2__ SCIC_SDS_PORT_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_LOG_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIC_LOG_OBJECT_PORT ; 
 int /*<<< orphan*/  SCI_BASE_PORT_STATE_FAILED ; 
 scalar_t__ SCI_BASE_PORT_STATE_RESETTING ; 
 scalar_t__ SCI_BASE_PORT_STATE_STOPPED ; 
 scalar_t__ SCI_BASE_PORT_STATE_STOPPING ; 
 int /*<<< orphan*/  SCI_FAILURE_TIMEOUT ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_2__*) ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sci_base_state_machine_get_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_cb_port_stop_complete (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_port_get_controller (TYPE_2__*) ; 

void scic_sds_port_timeout_handler(
   void *port
)
{
   U32 current_state;
   SCIC_SDS_PORT_T * this_port;

   this_port = (SCIC_SDS_PORT_T *)port;
   current_state = sci_base_state_machine_get_state(
                           &this_port->parent.state_machine);

   if (current_state == SCI_BASE_PORT_STATE_RESETTING)
   {
      // if the port is still in the resetting state then the timeout fired
      // before the reset completed.
      sci_base_state_machine_change_state(
         &this_port->parent.state_machine,
         SCI_BASE_PORT_STATE_FAILED
      );
   }
   else if (current_state == SCI_BASE_PORT_STATE_STOPPED)
   {
      // if the port is stopped then the start request failed
      // In this case stay in the stopped state.
      SCIC_LOG_ERROR((
         sci_base_object_get_logger(this_port),
         SCIC_LOG_OBJECT_PORT,
         "SCIC Port 0x%x failed to stop before tiemout.\n",
         this_port
      ));
   }
   else if (current_state == SCI_BASE_PORT_STATE_STOPPING)
   {
      // if the port is still stopping then the stop has not completed
      scic_cb_port_stop_complete(
         scic_sds_port_get_controller(this_port),
         port,
         SCI_FAILURE_TIMEOUT
      );
   }
   else
   {
      // The port is in the ready state and we have a timer reporting a timeout
      // this should not happen.
      SCIC_LOG_ERROR((
         sci_base_object_get_logger(this_port),
         SCIC_LOG_OBJECT_PORT,
         "SCIC Port 0x%x is processing a timeout operation in state %d.\n",
         this_port, current_state
      ));
   }
}