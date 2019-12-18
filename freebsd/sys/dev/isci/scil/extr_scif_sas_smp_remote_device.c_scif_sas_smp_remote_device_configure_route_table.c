#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  curr_config_route_index; int /*<<< orphan*/  current_activity_phy_index; TYPE_4__* curr_config_route_destination_smp_phy; int /*<<< orphan*/  current_activity; } ;
struct TYPE_11__ {TYPE_3__ smp_device; } ;
struct TYPE_15__ {TYPE_2__* domain; TYPE_1__ protocol_device; } ;
struct TYPE_14__ {int /*<<< orphan*/  attached_sas_address; int /*<<< orphan*/  list_element; } ;
struct TYPE_12__ {int /*<<< orphan*/  controller; } ;
typedef  int /*<<< orphan*/  SCI_FAST_LIST_ELEMENT_T ;
typedef  TYPE_3__ SCIF_SAS_SMP_REMOTE_DEVICE_T ;
typedef  TYPE_4__ SCIF_SAS_SMP_PHY_T ;
typedef  TYPE_5__ SCIF_SAS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int SCIF_LOG_OBJECT_DOMAIN_DISCOVERY ; 
 int SCIF_LOG_OBJECT_REMOTE_DEVICE ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_CONFIG_ROUTE_TABLE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_5__*) ; 
 int /*<<< orphan*/ * sci_fast_list_get_next (int /*<<< orphan*/ *) ; 
 scalar_t__ sci_fast_list_get_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scif_cb_start_internal_io_task_schedule (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_sas_controller_start_high_priority_io ; 
 scalar_t__ scif_sas_smp_remote_device_do_config_route_info (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  scif_sas_smp_request_construct_config_route_info (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void scif_sas_smp_remote_device_configure_route_table(
   SCIF_SAS_REMOTE_DEVICE_T * device_being_config
)
{
   //go through the smp phy list of this_device.
   SCI_FAST_LIST_ELEMENT_T     * element =
      &(device_being_config->protocol_device.smp_device.curr_config_route_destination_smp_phy->list_element);
   SCIF_SAS_SMP_PHY_T          * curr_smp_phy = NULL;

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(device_being_config),
      SCIF_LOG_OBJECT_REMOTE_DEVICE | SCIF_LOG_OBJECT_DOMAIN_DISCOVERY,
      "scif_sas_smp_remote_device_configure_route_table(0x%x) enter\n",
      device_being_config
   ));

   device_being_config->protocol_device.smp_device.current_activity =
      SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_CONFIG_ROUTE_TABLE;

   while (element != NULL)
   {
      curr_smp_phy = (SCIF_SAS_SMP_PHY_T*) sci_fast_list_get_object(element);
      element = sci_fast_list_get_next(element);

      //check if this phy needs to be added to the expander's route table.
      if (scif_sas_smp_remote_device_do_config_route_info(
             device_being_config, curr_smp_phy) == TRUE )
      {
         SCIF_SAS_SMP_REMOTE_DEVICE_T * smp_remote_device =
            &device_being_config->protocol_device.smp_device;

         smp_remote_device->curr_config_route_destination_smp_phy =
            curr_smp_phy;

         //Then config this_device's route table entry at the phy and next route_index.
         //send config_route_info using curr_smp_phy.phy_identifier and sas_address.
         scif_sas_smp_request_construct_config_route_info(
            device_being_config->domain->controller,
            device_being_config,
            smp_remote_device->current_activity_phy_index,
            smp_remote_device->curr_config_route_index,
            curr_smp_phy->attached_sas_address,
            FALSE
         );

         //schedule the DPC.
         scif_cb_start_internal_io_task_schedule(
            device_being_config->domain->controller,
            scif_sas_controller_start_high_priority_io,
            device_being_config->domain->controller
         );

         //stop here, we need to wait for config route info's response then send
         //the next one.
         break;
      }
   }
}