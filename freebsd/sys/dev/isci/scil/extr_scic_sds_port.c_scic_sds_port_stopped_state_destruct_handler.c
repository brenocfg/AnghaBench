#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  state_machine; } ;
struct TYPE_4__ {TYPE_1__ parent; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_BASE_PORT_T ;
typedef  TYPE_2__ SCIC_SDS_PORT_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_base_state_machine_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
SCI_STATUS scic_sds_port_stopped_state_destruct_handler(
   SCI_BASE_PORT_T *port
)
{
   SCIC_SDS_PORT_T *this_port = (SCIC_SDS_PORT_T *)port;

   sci_base_state_machine_stop(&this_port->parent.state_machine);

   return SCI_SUCCESS;
}