#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  state_machine; } ;
struct TYPE_5__ {scalar_t__ started_request_count; TYPE_1__ parent; } ;
typedef  int /*<<< orphan*/  SCI_BASE_OBJECT_T ;
typedef  TYPE_2__ SCIC_SDS_PORT_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_BASE_PORT_STATE_STOPPED ; 
 int /*<<< orphan*/  SCI_BASE_PORT_STATE_STOPPING ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_port_set_base_state_handlers (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void scic_sds_port_stopping_state_enter(
   SCI_BASE_OBJECT_T *object
)
{
   SCIC_SDS_PORT_T *this_port;
   this_port = (SCIC_SDS_PORT_T *)object;

   scic_sds_port_set_base_state_handlers(
      this_port, SCI_BASE_PORT_STATE_STOPPING
   );

   if (this_port->started_request_count == 0)
   {
      sci_base_state_machine_change_state(
         &this_port->parent.state_machine,
         SCI_BASE_PORT_STATE_STOPPED
      );
   }
}