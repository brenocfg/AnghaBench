#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/ * port_table; } ;
struct TYPE_12__ {size_t phy_index; } ;
struct TYPE_11__ {TYPE_2__** phy_table; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  TYPE_1__ SCIC_SDS_PORT_T ;
typedef  TYPE_2__ SCIC_SDS_PHY_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_FAILURE ; 
 TYPE_2__* SCI_INVALID_HANDLE ; 
 size_t SCI_MAX_PORTS ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 TYPE_1__* scic_sds_phy_get_port (TYPE_2__*) ; 
 int /*<<< orphan*/  scic_sds_phy_set_port (TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* scic_sds_port_get_controller (TYPE_1__*) ; 

SCI_STATUS scic_sds_port_clear_phy(
   SCIC_SDS_PORT_T *port,
   SCIC_SDS_PHY_T  *phy
)
{
   // Make sure that this phy is part of this port
   if (
           (port->phy_table[phy->phy_index] == phy)
        && (scic_sds_phy_get_port(phy) == port)
      )
   {
      // Yep it is assigned to this port so remove it
      scic_sds_phy_set_port(
         phy,
         &scic_sds_port_get_controller(port)->port_table[SCI_MAX_PORTS]
      );

      port->phy_table[phy->phy_index] = SCI_INVALID_HANDLE;

      return SCI_SUCCESS;
   }

   return SCI_FAILURE;
}