#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * owning_port; scalar_t__ bcn_received_while_port_unassigned; } ;
typedef  int /*<<< orphan*/  SCIC_SDS_PORT_T ;
typedef  TYPE_1__ SCIC_SDS_PHY_T ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  scic_sds_port_broadcast_change_received (int /*<<< orphan*/ *,TYPE_1__*) ; 

void scic_sds_phy_set_port(
   SCIC_SDS_PHY_T * this_phy,
   SCIC_SDS_PORT_T * the_port
)
{
   this_phy->owning_port = the_port;

   if (this_phy->bcn_received_while_port_unassigned)
   {
      this_phy->bcn_received_while_port_unassigned = FALSE;
      scic_sds_port_broadcast_change_received(this_phy->owning_port, this_phy);
   }
}