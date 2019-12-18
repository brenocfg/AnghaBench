#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/ * list_head; } ;
struct TYPE_17__ {TYPE_5__* curr_config_route_destination_smp_phy; TYPE_1__ smp_phy_list; } ;
struct TYPE_15__ {TYPE_6__ smp_device; } ;
struct TYPE_19__ {TYPE_4__ protocol_device; } ;
struct TYPE_14__ {TYPE_2__* attached_phy; } ;
struct TYPE_18__ {scalar_t__ routing_attribute; scalar_t__ attached_device_type; TYPE_3__ u; } ;
struct TYPE_16__ {scalar_t__ owning_device; } ;
struct TYPE_13__ {TYPE_8__* owning_device; } ;
typedef  int /*<<< orphan*/  SCI_FAST_LIST_ELEMENT_T ;
typedef  TYPE_6__ SCIF_SAS_SMP_REMOTE_DEVICE_T ;
typedef  TYPE_7__ SCIF_SAS_SMP_PHY_T ;
typedef  TYPE_8__ SCIF_SAS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int SCIF_LOG_OBJECT_DOMAIN_DISCOVERY ; 
 int SCIF_LOG_OBJECT_REMOTE_DEVICE ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ SMP_EDGE_EXPANDER_DEVICE ; 
 scalar_t__ TABLE_ROUTING_ATTRIBUTE ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_8__*) ; 
 int /*<<< orphan*/ * sci_fast_list_get_next (int /*<<< orphan*/ *) ; 
 scalar_t__ sci_fast_list_get_object (int /*<<< orphan*/ *) ; 

SCIF_SAS_REMOTE_DEVICE_T * scif_sas_remote_device_find_downstream_expander(
   SCIF_SAS_REMOTE_DEVICE_T * this_device
)
{
   SCIF_SAS_SMP_REMOTE_DEVICE_T * this_smp_remote_device =
      &this_device->protocol_device.smp_device;

   SCIF_SAS_REMOTE_DEVICE_T    * downstream_expander = NULL;

   SCI_FAST_LIST_ELEMENT_T     * element = this_smp_remote_device->smp_phy_list.list_head;
   SCIF_SAS_SMP_PHY_T          * curr_smp_phy = NULL;

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(this_device),
      SCIF_LOG_OBJECT_REMOTE_DEVICE | SCIF_LOG_OBJECT_DOMAIN_DISCOVERY,
      "scif_sas_remote_device_find_downstream_expander(0x%x) enter\n",
      this_device
   ));

   while (element != NULL)
   {
      curr_smp_phy = (SCIF_SAS_SMP_PHY_T*) sci_fast_list_get_object(element);
      element = sci_fast_list_get_next(element);

      if ( curr_smp_phy->routing_attribute == TABLE_ROUTING_ATTRIBUTE
          && curr_smp_phy->attached_device_type == SMP_EDGE_EXPANDER_DEVICE
          && curr_smp_phy->u.attached_phy != NULL)
      {
         //set the current_activity and current_config_route_index for that
         //upstream expander.
         downstream_expander = curr_smp_phy->u.attached_phy->owning_device;

         if ( downstream_expander->protocol_device.smp_device.curr_config_route_destination_smp_phy != NULL
             && downstream_expander->protocol_device.smp_device.curr_config_route_destination_smp_phy->owning_device ==
                this_smp_remote_device->curr_config_route_destination_smp_phy->owning_device )
            return downstream_expander;
      }
   }

   return NULL;
}