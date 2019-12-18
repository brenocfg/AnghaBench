#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  SCIF_SAS_SMP_PHY_T ;

/* Variables and functions */
 int /*<<< orphan*/ * scif_sas_smp_phy_find_next_phy_in_wide_port (int /*<<< orphan*/ *) ; 

SCIF_SAS_SMP_PHY_T * scif_sas_smp_phy_find_highest_phy_in_wide_port(
   SCIF_SAS_SMP_PHY_T * this_smp_phy
)
{
   SCIF_SAS_SMP_PHY_T * next_phy =
      scif_sas_smp_phy_find_next_phy_in_wide_port(this_smp_phy);
   SCIF_SAS_SMP_PHY_T * highest_phy = this_smp_phy;

   while(next_phy != NULL )
   {
      highest_phy = next_phy;
      next_phy =
         scif_sas_smp_phy_find_next_phy_in_wide_port(next_phy);
   }

   return highest_phy;
}