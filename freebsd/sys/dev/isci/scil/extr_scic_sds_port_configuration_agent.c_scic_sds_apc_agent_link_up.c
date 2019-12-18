#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int phy_ready_mask; } ;
struct TYPE_11__ {scalar_t__ current_state_id; } ;
struct TYPE_10__ {TYPE_2__ state_machine; } ;
struct TYPE_12__ {TYPE_1__ parent; } ;
typedef  TYPE_3__ SCIC_SDS_PORT_T ;
typedef  TYPE_4__ SCIC_SDS_PORT_CONFIGURATION_AGENT_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_PHY_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int SCIC_LOG_OBJECT_CONTROLLER ; 
 int SCIC_LOG_OBJECT_PHY ; 
 int SCIC_LOG_OBJECT_PORT ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIC_SDS_APC_WAIT_LINK_UP_NOTIFICATION ; 
 scalar_t__ SCI_BASE_PORT_STATE_RESETTING ; 
 TYPE_3__* SCI_INVALID_HANDLE ; 
 int /*<<< orphan*/  sci_base_object_get_logger (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_apc_agent_start_timer (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int scic_sds_phy_get_index (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_port_link_up (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
void scic_sds_apc_agent_link_up(
   SCIC_SDS_CONTROLLER_T               * controller,
   SCIC_SDS_PORT_CONFIGURATION_AGENT_T * port_agent,
   SCIC_SDS_PORT_T                     * port,
   SCIC_SDS_PHY_T                      * phy
)
{
   SCIC_LOG_TRACE((
      sci_base_object_get_logger(controller),
      SCIC_LOG_OBJECT_CONTROLLER | SCIC_LOG_OBJECT_PORT | SCIC_LOG_OBJECT_PHY,
      "scic_sds_apc_agent_link_up(0x%08x, 0x%08x, 0x%08x, 0x%08x) enter\n",
      controller, port_agent, port, phy
   ));

   //the phy is not the part of this port, configure the port with this phy
   if (port == SCI_INVALID_HANDLE)
   {
      port_agent->phy_ready_mask |= (1 << scic_sds_phy_get_index(phy));

      scic_sds_apc_agent_start_timer(
         controller, port_agent, phy, SCIC_SDS_APC_WAIT_LINK_UP_NOTIFICATION
      );
   }
   else
   {
      //the phy is already the part of the port

      //if the PORT'S state is resetting then the link up is from port hard reset
      //in this case, we need to tell the port that link up is received
      if (  SCI_BASE_PORT_STATE_RESETTING
            == port->parent.state_machine.current_state_id
         )
      {
         //notify the port that port needs to be ready
         port_agent->phy_ready_mask |= (1 << scic_sds_phy_get_index(phy));
         scic_sds_port_link_up(port, phy);
      }
      else
      {
         ASSERT (0);
      }
   }
}