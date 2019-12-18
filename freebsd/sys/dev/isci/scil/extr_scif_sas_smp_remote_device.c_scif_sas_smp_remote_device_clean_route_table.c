#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ curr_config_route_index; scalar_t__ expander_route_indexes; scalar_t__ current_activity_phy_index; scalar_t__ number_of_phys; int /*<<< orphan*/  current_activity; int /*<<< orphan*/  is_route_table_cleaned; TYPE_1__* config_route_smp_phy_anchor; } ;
struct TYPE_11__ {TYPE_6__ smp_device; } ;
struct TYPE_13__ {int /*<<< orphan*/  domain; TYPE_2__ protocol_device; } ;
struct TYPE_12__ {scalar_t__ routing_attribute; scalar_t__ phy_identifier; scalar_t__ config_route_table_index_anchor; } ;
struct TYPE_10__ {scalar_t__ phy_identifier; } ;
typedef  TYPE_3__ SCIF_SAS_SMP_PHY_T ;
typedef  TYPE_4__ SCIF_SAS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int SCIF_LOG_OBJECT_DOMAIN_DISCOVERY ; 
 int SCIF_LOG_OBJECT_REMOTE_DEVICE ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_NONE ; 
 scalar_t__ TABLE_ROUTING_ATTRIBUTE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_4__*) ; 
 int /*<<< orphan*/  scif_sas_domain_continue_discover (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_sas_smp_remote_device_clean_route_table_entry (TYPE_4__*) ; 
 TYPE_3__* scif_sas_smp_remote_device_find_smp_phy_by_id (scalar_t__,TYPE_6__*) ; 

void scif_sas_smp_remote_device_clean_route_table(
   SCIF_SAS_REMOTE_DEVICE_T * fw_device
)
{
   SCIF_SAS_SMP_PHY_T * smp_phy_being_config;

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_device),
      SCIF_LOG_OBJECT_REMOTE_DEVICE | SCIF_LOG_OBJECT_DOMAIN_DISCOVERY,
      "scif_sas_smp_remote_device_clean_route_table(0x%x) enter\n",
      fw_device
   ));

   //from anchors, start to clean all the other route table entries.
   fw_device->protocol_device.smp_device.curr_config_route_index++;

   if ( fw_device->protocol_device.smp_device.curr_config_route_index >=
           fw_device->protocol_device.smp_device.expander_route_indexes )
   {
      fw_device->protocol_device.smp_device.curr_config_route_index = 0;

      do //find next table attribute PHY.
      {
         fw_device->protocol_device.smp_device.current_activity_phy_index++;
         if (fw_device->protocol_device.smp_device.current_activity_phy_index ==
                fw_device->protocol_device.smp_device.number_of_phys)
            fw_device->protocol_device.smp_device.current_activity_phy_index=0;

         //phy_index changed, so update the smp_phy_being_config.
         smp_phy_being_config =
            scif_sas_smp_remote_device_find_smp_phy_by_id(
               fw_device->protocol_device.smp_device.current_activity_phy_index,
               &(fw_device->protocol_device.smp_device)
            );
      } while( smp_phy_being_config->routing_attribute != TABLE_ROUTING_ATTRIBUTE );

      if ( smp_phy_being_config->phy_identifier !=
              fw_device->protocol_device.smp_device.config_route_smp_phy_anchor->phy_identifier)
      {
         if (smp_phy_being_config->config_route_table_index_anchor != 0)
            fw_device->protocol_device.smp_device.curr_config_route_index =
               smp_phy_being_config->config_route_table_index_anchor + 1;
         else
            fw_device->protocol_device.smp_device.curr_config_route_index = 0;
      }
   }

   if ( !(fw_device->protocol_device.smp_device.current_activity_phy_index ==
             fw_device->protocol_device.smp_device.config_route_smp_phy_anchor->phy_identifier
          && fw_device->protocol_device.smp_device.curr_config_route_index == 0)
      )
   {
      //clean this route entry.
      scif_sas_smp_remote_device_clean_route_table_entry(fw_device);
   }
   else
   {
      fw_device->protocol_device.smp_device.is_route_table_cleaned = TRUE;

      //set this device's activity to NON.
      fw_device->protocol_device.smp_device.current_activity =
         SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_NONE;

      //we need to notify domain that this device finished config route table, domain
      //may pick up other activities (i.e. Discover) for other expanders.
      scif_sas_domain_continue_discover(fw_device->domain);
   }
}