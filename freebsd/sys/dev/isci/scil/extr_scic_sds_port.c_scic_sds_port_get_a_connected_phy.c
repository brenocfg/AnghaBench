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
typedef  size_t U32 ;
struct TYPE_4__ {int /*<<< orphan*/ ** phy_table; } ;
typedef  TYPE_1__ SCIC_SDS_PORT_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_PHY_T ;

/* Variables and functions */
 size_t SCI_MAX_PHYS ; 
 scalar_t__ scic_sds_port_active_phy (TYPE_1__*,int /*<<< orphan*/ *) ; 

SCIC_SDS_PHY_T * scic_sds_port_get_a_connected_phy(
   SCIC_SDS_PORT_T *this_port
)
{
   U32             index;
   SCIC_SDS_PHY_T *phy;

   for (index = 0; index < SCI_MAX_PHYS; index++)
   {
      // Ensure that the phy is both part of the port and currently
      // connected to the remote end-point.
      phy = this_port->phy_table[index];
      if (
            (phy != NULL)
         && scic_sds_port_active_phy(this_port, phy)
         )
      {
         return phy;
      }
   }

   return NULL;
}