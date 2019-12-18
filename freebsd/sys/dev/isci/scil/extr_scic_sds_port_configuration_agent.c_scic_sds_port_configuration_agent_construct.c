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
typedef  size_t U32 ;
struct TYPE_5__ {int phy_configured_mask; int phy_ready_mask; TYPE_1__* phy_valid_port_range; int /*<<< orphan*/ * timer; int /*<<< orphan*/  timer_pending; int /*<<< orphan*/ * link_down_handler; int /*<<< orphan*/ * link_up_handler; } ;
struct TYPE_4__ {scalar_t__ max_index; scalar_t__ min_index; } ;
typedef  TYPE_2__ SCIC_SDS_PORT_CONFIGURATION_AGENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 size_t SCI_MAX_PORTS ; 

void scic_sds_port_configuration_agent_construct(
   SCIC_SDS_PORT_CONFIGURATION_AGENT_T * port_agent
)
{
   U32 index;

   port_agent->phy_configured_mask = 0x00;
   port_agent->phy_ready_mask = 0x00;

   port_agent->link_up_handler = NULL;
   port_agent->link_down_handler = NULL;

   port_agent->timer_pending = FALSE;
   port_agent->timer = NULL;

   for (index = 0; index < SCI_MAX_PORTS; index++)
   {
      port_agent->phy_valid_port_range[index].min_index = 0;
      port_agent->phy_valid_port_range[index].max_index = 0;
   }
}