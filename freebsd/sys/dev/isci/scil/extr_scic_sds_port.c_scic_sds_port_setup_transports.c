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
typedef  int U8 ;
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_3__ {int active_phy_mask; int /*<<< orphan*/ * phy_table; } ;
typedef  TYPE_1__ SCIC_SDS_PORT_T ;

/* Variables and functions */
 int SCI_MAX_PHYS ; 
 int /*<<< orphan*/  scic_sds_phy_setup_transport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void scic_sds_port_setup_transports(
   SCIC_SDS_PORT_T * this_port,
   U32               device_id
)
{
   U8 index;

   for (index = 0; index < SCI_MAX_PHYS; index++)
   {
      if (this_port->active_phy_mask & (1 << index))
      {
         scic_sds_phy_setup_transport(this_port->phy_table[index], device_id);
      }
   }
}