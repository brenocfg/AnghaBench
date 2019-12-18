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
struct TYPE_5__ {int /*<<< orphan*/  not_ready_reason; } ;
typedef  int /*<<< orphan*/  SCI_BASE_OBJECT_T ;
typedef  TYPE_1__ SCIC_SDS_PORT_T ;

/* Variables and functions */
 int /*<<< orphan*/  scic_cb_port_not_ready (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_port_abort_dummy_request (TYPE_1__*) ; 
 int /*<<< orphan*/  scic_sds_port_get_controller (TYPE_1__*) ; 

__attribute__((used)) static
void scic_sds_port_ready_substate_operational_exit(
   SCI_BASE_OBJECT_T *object
)
{
   SCIC_SDS_PORT_T *this_port = (SCIC_SDS_PORT_T *)object;

   // Kill the dummy task for this port if it has not yet posted
   // the hardware will treat this as a NOP and just return abort
   // complete.
   scic_sds_port_abort_dummy_request(this_port);

   scic_cb_port_not_ready(
      scic_sds_port_get_controller(this_port),
      this_port,
      this_port->not_ready_reason
   );
}