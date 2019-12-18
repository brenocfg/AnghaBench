#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int phy_ready_mask; int phy_configured_mask; int /*<<< orphan*/  timer; scalar_t__ timer_pending; } ;
typedef  int /*<<< orphan*/  SCIC_SDS_PORT_T ;
typedef  TYPE_1__ SCIC_SDS_PORT_CONFIGURATION_AGENT_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_PHY_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int SCIC_LOG_OBJECT_CONTROLLER ; 
 int SCIC_LOG_OBJECT_PHY ; 
 int SCIC_LOG_OBJECT_PORT ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIC_SDS_MPC_RECONFIGURATION_TIMEOUT ; 
 int /*<<< orphan*/ * SCI_INVALID_HANDLE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  sci_base_object_get_logger (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_cb_timer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int scic_sds_phy_get_index (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_port_link_down (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
void scic_sds_mpc_agent_link_down(
   SCIC_SDS_CONTROLLER_T               * controller,
   SCIC_SDS_PORT_CONFIGURATION_AGENT_T * port_agent,
   SCIC_SDS_PORT_T                     * port,
   SCIC_SDS_PHY_T                      * phy
)
{
   SCIC_LOG_TRACE((
      sci_base_object_get_logger(controller),
      SCIC_LOG_OBJECT_CONTROLLER | SCIC_LOG_OBJECT_PORT | SCIC_LOG_OBJECT_PHY,
      "scic_sds_mpc_agent_link_down(0x%08x, 0x%08x, 0x%08x, 0x%08x) enter\n",
      controller, port_agent, port, phy
   ));

   if (port != SCI_INVALID_HANDLE)
   {
      // If we can form a new port from the remainder of the phys then we want
      // to start the timer to allow the SCI User to cleanup old devices and
      // rediscover the port before rebuilding the port with the phys that
      // remain in the ready state.
      port_agent->phy_ready_mask &= ~(1 << scic_sds_phy_get_index(phy));
      port_agent->phy_configured_mask &= ~(1 << scic_sds_phy_get_index(phy));

      // Check to see if there are more phys waiting to be configured into a port.
      // If there are allow the SCI User to tear down this port, if necessary, and
      // then reconstruc the port after the timeout.
      if (
            (port_agent->phy_configured_mask == 0x0000)
         && (port_agent->phy_ready_mask != 0x0000)
         && !port_agent->timer_pending
         )
      {
         port_agent->timer_pending = TRUE;

         scic_cb_timer_start(
            controller,
            port_agent->timer,
            SCIC_SDS_MPC_RECONFIGURATION_TIMEOUT
         );
      }

      scic_sds_port_link_down(port, phy);
   }
}