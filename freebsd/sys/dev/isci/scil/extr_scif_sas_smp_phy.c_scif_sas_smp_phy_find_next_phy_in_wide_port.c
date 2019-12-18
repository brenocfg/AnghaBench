#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ high; scalar_t__ low; } ;
struct TYPE_6__ {TYPE_1__ attached_sas_address; int /*<<< orphan*/  list_element; } ;
typedef  int /*<<< orphan*/  SCI_FAST_LIST_ELEMENT_T ;
typedef  TYPE_2__ SCIF_SAS_SMP_PHY_T ;

/* Variables and functions */
 int /*<<< orphan*/ * sci_fast_list_get_next (int /*<<< orphan*/ *) ; 
 scalar_t__ sci_fast_list_get_object (int /*<<< orphan*/ *) ; 

SCIF_SAS_SMP_PHY_T * scif_sas_smp_phy_find_next_phy_in_wide_port(
   SCIF_SAS_SMP_PHY_T * this_smp_phy
)
{
   SCI_FAST_LIST_ELEMENT_T * next_phy_element = sci_fast_list_get_next(
      &(this_smp_phy->list_element) );

   SCIF_SAS_SMP_PHY_T * next_phy;

   while (next_phy_element != NULL)
   {
      next_phy = (SCIF_SAS_SMP_PHY_T *)sci_fast_list_get_object(next_phy_element);

      next_phy_element = sci_fast_list_get_next( &(next_phy->list_element));

      if (next_phy->attached_sas_address.high == this_smp_phy->attached_sas_address.high
          &&next_phy->attached_sas_address.low == this_smp_phy->attached_sas_address.low)
         return next_phy;
   }

   return NULL;
}