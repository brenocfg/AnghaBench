#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t phy_index; } ;
struct TYPE_9__ {scalar_t__* phy_table; int /*<<< orphan*/  physical_port_index; int /*<<< orphan*/  logical_port_index; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  TYPE_1__ SCIC_SDS_PORT_T ;
typedef  TYPE_2__ SCIC_SDS_PHY_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_FAILURE ; 
 scalar_t__ SCI_INVALID_HANDLE ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 scalar_t__ scic_sds_phy_get_port (TYPE_2__*) ; 
 int /*<<< orphan*/  scic_sds_phy_set_port (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ scic_sds_port_is_valid_phy_assignment (TYPE_1__*,size_t) ; 

SCI_STATUS scic_sds_port_set_phy(
   SCIC_SDS_PORT_T *port,
   SCIC_SDS_PHY_T  *phy
)
{
   // Check to see if we can add this phy to a port
   // that means that the phy is not part of a port and that the port does
   // not already have a phy assinged to the phy index.
   if (
         (port->phy_table[phy->phy_index] == SCI_INVALID_HANDLE)
      && (scic_sds_phy_get_port(phy) == SCI_INVALID_HANDLE)
      && scic_sds_port_is_valid_phy_assignment(port, phy->phy_index)
      )
   {
      // Phy is being added in the stopped state so we are in MPC mode
      // make logical port index = physical port index
      port->logical_port_index = port->physical_port_index;
      port->phy_table[phy->phy_index] = phy;
      scic_sds_phy_set_port(phy, port);

      return SCI_SUCCESS;
   }

   return SCI_FAILURE;
}