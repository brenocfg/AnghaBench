#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t U8 ;
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_2__ {int /*<<< orphan*/ ** phy_table; } ;
typedef  scalar_t__ SCI_PORT_HANDLE_T ;
typedef  TYPE_1__ SCIC_SDS_PORT_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_PHY_T ;

/* Variables and functions */
 size_t SCI_MAX_PHYS ; 
 int /*<<< orphan*/  SCU_SAS_LLCTL_READ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCU_SAS_LLCTL_WRITE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void scic_port_enable_broadcast_change_notification(
   SCI_PORT_HANDLE_T  port
)
{
   SCIC_SDS_PORT_T * this_port = (SCIC_SDS_PORT_T *)port;
   SCIC_SDS_PHY_T * phy;
   U32 register_value;
   U8 index;

   // Loop through all of the phys to enable BCN.
   for (index = 0; index < SCI_MAX_PHYS; index++)
   {
      phy = this_port->phy_table[index];
      if ( phy != NULL)
      {
         register_value = SCU_SAS_LLCTL_READ(phy);

         // clear the bit by writing 1.
         SCU_SAS_LLCTL_WRITE(phy, register_value);
      }
   }
}