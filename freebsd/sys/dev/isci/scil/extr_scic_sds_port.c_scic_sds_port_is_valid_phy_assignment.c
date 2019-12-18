#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int U32 ;
struct TYPE_11__ {int physical_port_index; TYPE_4__* owning_controller; int /*<<< orphan*/ ** phy_table; } ;
struct TYPE_8__ {TYPE_1__* phys; } ;
struct TYPE_9__ {TYPE_2__ sds1; } ;
struct TYPE_10__ {TYPE_3__ user_parameters; } ;
struct TYPE_7__ {scalar_t__ max_speed_generation; } ;
typedef  TYPE_5__ SCIC_SDS_PORT_T ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int SCI_MAX_PHYS ; 
 int /*<<< orphan*/  TRUE ; 

BOOL scic_sds_port_is_valid_phy_assignment(
   SCIC_SDS_PORT_T *this_port,
   U32              phy_index
)
{
   // Initialize to invalid value.
   U32  existing_phy_index = SCI_MAX_PHYS;
   U32  index;

   if ((this_port->physical_port_index == 1) && (phy_index != 1))
   {
      return FALSE;
   }

   if (this_port->physical_port_index == 3 && phy_index != 3)
   {
      return FALSE;
   }

   if (
          (this_port->physical_port_index == 2)
       && ((phy_index == 0) || (phy_index == 1))
      )
   {
      return FALSE;
   }

   for (index = 0; index < SCI_MAX_PHYS; index++)
   {
      if (  (this_port->phy_table[index] != NULL)
         && (index != phy_index) )
      {
         existing_phy_index = index;
      }
   }

   // Ensure that all of the phys in the port are capable of
   // operating at the same maximum link rate.
   if (
         (existing_phy_index < SCI_MAX_PHYS)
      && (this_port->owning_controller->user_parameters.sds1.phys[
             phy_index].max_speed_generation !=
          this_port->owning_controller->user_parameters.sds1.phys[
             existing_phy_index].max_speed_generation)
      )
      return FALSE;

   return TRUE;
}