#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int U32 ;
typedef  int U16 ;
struct TYPE_11__ {int next_phy_to_start; scalar_t__ phy_startup_timer_pending; int /*<<< orphan*/ * phy_table; } ;
struct TYPE_10__ {int phy_configured_mask; int phy_ready_mask; scalar_t__ timer_pending; } ;
typedef  TYPE_1__ SCIC_SDS_PORT_CONFIGURATION_AGENT_T ;
typedef  TYPE_2__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int SCIC_LOG_OBJECT_CONTROLLER ; 
 int SCIC_LOG_OBJECT_PORT ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int SCI_MAX_PHYS ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_2__*) ; 
 int /*<<< orphan*/  scic_sds_apc_agent_configure_ports (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_1__* scic_sds_controller_get_port_configuration_agent (TYPE_2__*) ; 
 scalar_t__ scic_sds_controller_is_start_complete (TYPE_2__*) ; 
 int /*<<< orphan*/  scic_sds_controller_port_agent_configured_ports (TYPE_2__*) ; 

__attribute__((used)) static
void scic_sds_apc_agent_timeout_handler(
   void * object
)
{
   U32 index;
   SCIC_SDS_PORT_CONFIGURATION_AGENT_T * port_agent;
   SCIC_SDS_CONTROLLER_T * controller = (SCIC_SDS_CONTROLLER_T *)object;
   U16 configure_phy_mask;

   port_agent = scic_sds_controller_get_port_configuration_agent(controller);

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(controller),
      SCIC_LOG_OBJECT_CONTROLLER | SCIC_LOG_OBJECT_PORT,
      "scic_sds_apc_agent_timeout_handler(0x%08x) enter\n",
      controller
   ));

   port_agent->timer_pending = FALSE;

   configure_phy_mask = ~port_agent->phy_configured_mask & port_agent->phy_ready_mask;

   if (configure_phy_mask != 0x00)
   {
      for (index = 0; index < SCI_MAX_PHYS; index++)
      {
         if (configure_phy_mask & (1 << index))
         {
            scic_sds_apc_agent_configure_ports(
               controller, port_agent, &controller->phy_table[index], FALSE
            );
         }
      }

      //Notify the controller ports are configured.
      if (
            (port_agent->phy_ready_mask == port_agent->phy_configured_mask) &&
            (controller->next_phy_to_start == SCI_MAX_PHYS) &&
            (controller->phy_startup_timer_pending == FALSE)
         )
      {
         // The controller has successfully finished the start process.
         // Inform the SCI Core user and transition to the READY state.
         if (scic_sds_controller_is_start_complete(controller) == TRUE)
         {
            scic_sds_controller_port_agent_configured_ports(controller);
         }
      }
   }
}