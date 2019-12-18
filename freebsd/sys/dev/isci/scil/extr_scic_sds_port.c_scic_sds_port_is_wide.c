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
typedef  size_t U32 ;
struct TYPE_3__ {int /*<<< orphan*/ ** phy_table; } ;
typedef  TYPE_1__ SCIC_SDS_PORT_T ;
typedef  int BOOL ;

/* Variables and functions */
 size_t SCI_MAX_PHYS ; 

__attribute__((used)) static
BOOL scic_sds_port_is_wide(
   SCIC_SDS_PORT_T *this_port
)
{
   U32 index;
   U32 phy_count = 0;

   for (index = 0; index < SCI_MAX_PHYS; index++)
   {
      if (this_port->phy_table[index] != NULL)
      {
         phy_count++;
      }
   }

   return (phy_count != 1);
}