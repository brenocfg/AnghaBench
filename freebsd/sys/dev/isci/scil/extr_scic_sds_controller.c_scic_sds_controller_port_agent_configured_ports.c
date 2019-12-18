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
typedef  int /*<<< orphan*/  SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  scic_sds_controller_transition_to_ready (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void scic_sds_controller_port_agent_configured_ports(
   SCIC_SDS_CONTROLLER_T * this_controller
)
{
   //simply transit to ready. The function below checks the controller state
   scic_sds_controller_transition_to_ready(
      this_controller, SCI_SUCCESS
   );
}