#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int routing_attribute; TYPE_3__* owning_device; } ;
struct TYPE_7__ {int /*<<< orphan*/  is_table_to_table_supported; } ;
struct TYPE_8__ {TYPE_1__ smp_device; } ;
struct TYPE_9__ {TYPE_2__ protocol_device; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  TYPE_4__ SCIF_SAS_SMP_PHY_T ;

/* Variables and functions */
 int DIRECT_ROUTING_ATTRIBUTE ; 
 int /*<<< orphan*/  SCI_FAILURE ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int TABLE_ROUTING_ATTRIBUTE ; 

SCI_STATUS scif_sas_smp_phy_verify_routing_attribute(
   SCIF_SAS_SMP_PHY_T * this_smp_phy,
   SCIF_SAS_SMP_PHY_T * attached_smp_phy
)
{
   SCI_STATUS status = SCI_SUCCESS;

   //expander phy with direct routing attribute can only connect to
   //phy with direct routing attribute.
   if ( this_smp_phy->routing_attribute == DIRECT_ROUTING_ATTRIBUTE
         || attached_smp_phy->routing_attribute == DIRECT_ROUTING_ATTRIBUTE )
   {
      if ( (this_smp_phy->routing_attribute | attached_smp_phy->routing_attribute)
           != DIRECT_ROUTING_ATTRIBUTE )
         status = SCI_FAILURE;
   }

   if (this_smp_phy->routing_attribute == TABLE_ROUTING_ATTRIBUTE
       && attached_smp_phy->routing_attribute == TABLE_ROUTING_ATTRIBUTE)
   {
      if ( ! this_smp_phy->owning_device->protocol_device.smp_device.is_table_to_table_supported
         || !attached_smp_phy->owning_device->protocol_device.smp_device.is_table_to_table_supported )
      status = SCI_FAILURE;
   }

   return status;
}