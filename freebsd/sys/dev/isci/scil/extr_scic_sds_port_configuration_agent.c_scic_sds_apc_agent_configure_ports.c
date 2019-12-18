#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  enum SCIC_SDS_APC_ACTIVITY { ____Placeholder_SCIC_SDS_APC_ACTIVITY } SCIC_SDS_APC_ACTIVITY ;
typedef  scalar_t__ U8 ;
struct TYPE_18__ {size_t phy_index; } ;
struct TYPE_17__ {int phy_configured_mask; TYPE_1__* phy_valid_port_range; } ;
struct TYPE_16__ {int active_phy_mask; int physical_port_index; } ;
struct TYPE_15__ {scalar_t__ min_index; scalar_t__ max_index; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  scalar_t__ SCI_PORT_HANDLE_T ;
typedef  TYPE_2__ SCIC_SDS_PORT_T ;
typedef  TYPE_3__ SCIC_SDS_PORT_CONFIGURATION_AGENT_T ;
typedef  TYPE_4__ SCIC_SDS_PHY_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_CONTROLLER_T ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int SCIC_LOG_OBJECT_CONTROLLER ; 
 int SCIC_LOG_OBJECT_PHY ; 
 int SCIC_LOG_OBJECT_PORT ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
#define  SCIC_SDS_APC_ADD_PHY 130 
#define  SCIC_SDS_APC_SKIP_PHY 129 
#define  SCIC_SDS_APC_START_TIMER 128 
 int /*<<< orphan*/  SCIC_SDS_APC_WAIT_LINK_UP_NOTIFICATION ; 
 TYPE_2__* SCI_INVALID_HANDLE ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_base_object_get_logger (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_controller_get_port_handle (int /*<<< orphan*/ *,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  scic_sds_apc_agent_start_timer (int /*<<< orphan*/ *,TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_port_add_phy (TYPE_2__*,TYPE_4__*) ; 
 TYPE_2__* scic_sds_port_configuration_agent_find_port (int /*<<< orphan*/ *,TYPE_4__*) ; 
 scalar_t__ scic_sds_port_is_valid_phy_assignment (TYPE_2__*,size_t) ; 

__attribute__((used)) static
void scic_sds_apc_agent_configure_ports(
   SCIC_SDS_CONTROLLER_T               * controller,
   SCIC_SDS_PORT_CONFIGURATION_AGENT_T * port_agent,
   SCIC_SDS_PHY_T                      * phy,
   BOOL                                  start_timer
)
{
   U8 port_index;
   SCI_STATUS status;
   SCIC_SDS_PORT_T * port;
   SCI_PORT_HANDLE_T port_handle;
   enum SCIC_SDS_APC_ACTIVITY apc_activity = SCIC_SDS_APC_SKIP_PHY;

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(controller),
      SCIC_LOG_OBJECT_CONTROLLER | SCIC_LOG_OBJECT_PORT | SCIC_LOG_OBJECT_PHY,
      "scic_sds_apc_agent_configure_ports(0x%08x, 0x%08x, 0x%08x, %d) enter\n",
      controller, port_agent, phy, start_timer
   ));

   port = scic_sds_port_configuration_agent_find_port(controller, phy);

   if (port != SCI_INVALID_HANDLE)
   {
      if (scic_sds_port_is_valid_phy_assignment(port, phy->phy_index))
         apc_activity = SCIC_SDS_APC_ADD_PHY;
      else
         apc_activity = SCIC_SDS_APC_SKIP_PHY;
   }
   else
   {
      // There is no matching Port for this PHY so lets search through the
      // Ports and see if we can add the PHY to its own port or maybe start
      // the timer and wait to see if a wider port can be made.
      //
      // Note the break when we reach the condition of the port id == phy id
      for (
             port_index = port_agent->phy_valid_port_range[phy->phy_index].min_index;
             port_index <= port_agent->phy_valid_port_range[phy->phy_index].max_index;
             port_index++
          )
      {
         scic_controller_get_port_handle(controller, port_index, &port_handle);

         port = (SCIC_SDS_PORT_T *)port_handle;

         // First we must make sure that this PHY can be added to this Port.
         if (scic_sds_port_is_valid_phy_assignment(port, phy->phy_index))
         {
            // Port contains a PHY with a greater PHY ID than the current
            // PHY that has gone link up.  This phy can not be part of any
            // port so skip it and move on.
            if (port->active_phy_mask > (1 << phy->phy_index))
            {
               apc_activity = SCIC_SDS_APC_SKIP_PHY;
               break;
            }

            // We have reached the end of our Port list and have not found
            // any reason why we should not either add the PHY to the port
            // or wait for more phys to become active.
            if (port->physical_port_index == phy->phy_index)
            {
               // The Port either has no active PHYs.
               // Consider that if the port had any active PHYs we would have
               // or active PHYs with
               // a lower PHY Id than this PHY.
               if (apc_activity != SCIC_SDS_APC_START_TIMER)
               {
                  apc_activity = SCIC_SDS_APC_ADD_PHY;
               }

               break;
            }

            // The current Port has no active PHYs and this PHY could be part
            // of this Port.  Since we dont know as yet setup to start the
            // timer and see if there is a better configuration.
            if (port->active_phy_mask == 0)
            {
               apc_activity = SCIC_SDS_APC_START_TIMER;
            }
         }
         else if (port->active_phy_mask != 0)
         {
            // The Port has an active phy and the current Phy can not
            // participate in this port so skip the PHY and see if
            // there is a better configuration.
            apc_activity = SCIC_SDS_APC_SKIP_PHY;
         }
      }
   }

   // Check to see if the start timer operations should instead map to an
   // add phy operation.  This is caused because we have been waiting to
   // add a phy to a port but could not because the automatic port
   // configuration engine had a choice of possible ports for the phy.
   // Since we have gone through a timeout we are going to restrict the
   // choice to the smallest possible port.
   if (
         (start_timer == FALSE)
      && (apc_activity == SCIC_SDS_APC_START_TIMER)
      )
   {
      apc_activity = SCIC_SDS_APC_ADD_PHY;
   }

   switch (apc_activity)
   {
   case SCIC_SDS_APC_ADD_PHY:
      status = scic_sds_port_add_phy(port, phy);

      if (status == SCI_SUCCESS)
      {
         port_agent->phy_configured_mask |= (1 << phy->phy_index);
      }
      break;

   case SCIC_SDS_APC_START_TIMER:
      scic_sds_apc_agent_start_timer(
         controller, port_agent, phy, SCIC_SDS_APC_WAIT_LINK_UP_NOTIFICATION
      );
      break;

   case SCIC_SDS_APC_SKIP_PHY:
   default:
      // do nothing the PHY can not be made part of a port at this time.
      break;
   }
}