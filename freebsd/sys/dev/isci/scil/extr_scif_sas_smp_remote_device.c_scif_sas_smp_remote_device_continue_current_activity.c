#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_6__ ;
typedef  struct TYPE_39__   TYPE_5__ ;
typedef  struct TYPE_38__   TYPE_4__ ;
typedef  struct TYPE_37__   TYPE_3__ ;
typedef  struct TYPE_36__   TYPE_31__ ;
typedef  struct TYPE_35__   TYPE_2__ ;
typedef  struct TYPE_34__   TYPE_25__ ;
typedef  struct TYPE_33__   TYPE_1__ ;

/* Type definitions */
typedef  int U8 ;
typedef  int U32 ;
struct TYPE_40__ {int retry_count; } ;
struct TYPE_33__ {scalar_t__ current_activity; scalar_t__ curr_config_route_index; scalar_t__ is_route_table_cleaned; TYPE_3__* config_route_smp_phy_anchor; TYPE_3__* curr_config_route_destination_smp_phy; int /*<<< orphan*/  current_activity_phy_index; int /*<<< orphan*/ * smp_activity_timer; } ;
struct TYPE_35__ {TYPE_1__ smp_device; } ;
struct TYPE_39__ {TYPE_2__ protocol_device; TYPE_25__* domain; int /*<<< orphan*/  core_object; } ;
struct TYPE_38__ {scalar_t__ is_internal; } ;
struct TYPE_36__ {int /*<<< orphan*/ * owning_list; } ;
struct TYPE_37__ {scalar_t__ config_route_table_index_anchor; int /*<<< orphan*/  phy_identifier; TYPE_31__ list_element; } ;
struct TYPE_34__ {scalar_t__ controller; } ;
typedef  int /*<<< orphan*/  SCI_TIMER_CALLBACK_T ;
typedef  scalar_t__ SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_FAST_LIST_T ;
typedef  int /*<<< orphan*/  SCI_FAST_LIST_ELEMENT_T ;
typedef  int /*<<< orphan*/  SCI_CONTROLLER_HANDLE_T ;
typedef  TYPE_3__ SCIF_SAS_SMP_PHY_T ;
typedef  TYPE_4__ SCIF_SAS_REQUEST_T ;
typedef  TYPE_5__ SCIF_SAS_REMOTE_DEVICE_T ;
typedef  TYPE_6__ SCIF_SAS_IO_REQUEST_T ;
typedef  int /*<<< orphan*/  SCIF_SAS_INTERNAL_IO_REQUEST_T ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int SCIF_DOMAIN_DISCOVER_TIMEOUT ; 
 scalar_t__ SCIF_SAS_CONFIG_ROUTE_TABLE_ALL_PHYS ; 
 int SCIF_SAS_IO_RETRY_LIMIT ; 
 scalar_t__ SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_CLEAN_ROUTE_TABLE ; 
 scalar_t__ SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_CLEAR_AFFILIATION ; 
 scalar_t__ SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_CONFIG_ROUTE_TABLE ; 
 scalar_t__ SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_DISCOVER ; 
 scalar_t__ SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_NONE ; 
 scalar_t__ SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_SATA_SPINUP_HOLD_RELEASE ; 
 scalar_t__ SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_TARGET_RESET ; 
 scalar_t__ SCI_FAILURE_EXCEED_MAX_ROUTE_INDEX ; 
 scalar_t__ SCI_FAILURE_ILLEGAL_ROUTING_ATTRIBUTE_CONFIGURATION ; 
 scalar_t__ SCI_FAILURE_RETRY_REQUIRED ; 
 scalar_t__ SCI_SUCCESS ; 
 int /*<<< orphan*/  SMP_REQUEST_RETRY_WAIT_DURATION ; 
 TYPE_3__* sci_fast_list_get_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sci_fast_list_get_next (TYPE_31__*) ; 
 scalar_t__ sci_fast_list_get_object (int /*<<< orphan*/ *) ; 
 int scic_remote_device_get_suggested_reset_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * scif_cb_timer_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  scif_cb_timer_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_sas_domain_continue_discover (TYPE_25__*) ; 
 TYPE_5__* scif_sas_domain_get_device_by_containing_device (TYPE_25__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_sas_domain_remove_expander_device (TYPE_25__*,TYPE_5__*) ; 
 int /*<<< orphan*/  scif_sas_internal_io_request_complete (scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ scif_sas_smp_external_request_retry ; 
 TYPE_3__* scif_sas_smp_phy_find_next_phy_in_wide_port (TYPE_3__*) ; 
 int /*<<< orphan*/  scif_sas_smp_remote_device_clean_route_table (TYPE_5__*) ; 
 int /*<<< orphan*/  scif_sas_smp_remote_device_configure_route_table (TYPE_5__*) ; 
 int /*<<< orphan*/  scif_sas_smp_remote_device_continue_clear_affiliation (TYPE_5__*) ; 
 int /*<<< orphan*/  scif_sas_smp_remote_device_continue_discover (TYPE_5__*) ; 
 int /*<<< orphan*/  scif_sas_smp_remote_device_continue_target_reset (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  scif_sas_smp_remote_device_fail_discover (TYPE_5__*) ; 
 int /*<<< orphan*/  scif_sas_smp_remote_device_fail_target_reset (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  scif_sas_smp_remote_device_fail_target_spinup_hold_release (TYPE_5__*,TYPE_5__*) ; 
 scalar_t__ scif_sas_smp_remote_device_get_config_route_table_method (TYPE_5__*) ; 
 int /*<<< orphan*/  scif_sas_smp_remote_device_retry_internal_io (TYPE_5__*,int,int) ; 
 int /*<<< orphan*/  scif_sas_smp_remote_device_sata_spinup_hold_release (TYPE_5__*) ; 

void scif_sas_smp_remote_device_continue_current_activity(
   SCIF_SAS_REMOTE_DEVICE_T * fw_device,
   SCIF_SAS_REQUEST_T       * fw_request,
   SCI_STATUS                 status
)
{
   SCIF_SAS_IO_REQUEST_T * fw_io = (SCIF_SAS_IO_REQUEST_T *)fw_request;
   // save the retry count.
   U8 io_retry_count = fw_io->retry_count;

   if (fw_request->is_internal)
   {
      // Complete this internal io request now. We want to free this io before
      // we create another SMP request, which is going to happen soon.
      scif_sas_internal_io_request_complete(
         fw_device->domain->controller,
         (SCIF_SAS_INTERNAL_IO_REQUEST_T *)fw_request,
         SCI_SUCCESS
      );
   }

   if (fw_device->protocol_device.smp_device.current_activity ==
      SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_DISCOVER)
   {
      if (status == SCI_SUCCESS)
      {   //continue the discover process.
         scif_sas_smp_remote_device_continue_discover(fw_device);
      }
      else if (status == SCI_FAILURE_RETRY_REQUIRED)
      {
         //Retry the smp request. Since we are in the middle of Discover
         //process, all the smp requests are internal. A new smp request
         //will be created for retry.
         U32 retry_wait_duration = (SCIF_DOMAIN_DISCOVER_TIMEOUT / 2) / SCIF_SAS_IO_RETRY_LIMIT;

         if (io_retry_count < SCIF_SAS_IO_RETRY_LIMIT)
            scif_sas_smp_remote_device_retry_internal_io (
               fw_device, io_retry_count, retry_wait_duration);
         else
            scif_sas_smp_remote_device_fail_discover(fw_device);
      }
      else if (status == SCI_FAILURE_ILLEGAL_ROUTING_ATTRIBUTE_CONFIGURATION)
      {
         //remove this expander device and its child devices. No need to
         //continue the discover on this device.
         scif_sas_domain_remove_expander_device(fw_device->domain, fw_device);

         //continue the domain's smp discover.
         scif_sas_domain_continue_discover(fw_device->domain);
      }
      else
      {  //terminate the discover process.
         scif_sas_smp_remote_device_fail_discover(fw_device);
      }
   }
   else if (fw_device->protocol_device.smp_device.current_activity ==
      SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_TARGET_RESET)
   {
      if (status == SCI_SUCCESS)
      {   //continue the target reset process.
         scif_sas_smp_remote_device_continue_target_reset(
            fw_device, fw_request);
      }
      else if (status == SCI_FAILURE_RETRY_REQUIRED)
      {
         //Retry the same smp request. Since we are in the middle of Target
         //reset process, all the smp requests are using external resource.
         //We will use the exactly same memory to retry.
         if (io_retry_count < SCIF_SAS_IO_RETRY_LIMIT)
         {
            if (fw_device->protocol_device.smp_device.smp_activity_timer == NULL)
            {
               //create the timer to wait before retry.
               fw_device->protocol_device.smp_device.smp_activity_timer =
                  scif_cb_timer_create(
                  (SCI_CONTROLLER_HANDLE_T *)fw_device->domain->controller,
                  (SCI_TIMER_CALLBACK_T)scif_sas_smp_external_request_retry,
                  (void*)fw_request
               );
            }
            else
            {
               ASSERT(0);
            }

            //start the timer to wait
            scif_cb_timer_start(
               (SCI_CONTROLLER_HANDLE_T)fw_device->domain->controller,
               fw_device->protocol_device.smp_device.smp_activity_timer,
               SMP_REQUEST_RETRY_WAIT_DURATION  //20 miliseconds
            );
         }
         else
            scif_sas_smp_remote_device_fail_target_reset(fw_device, fw_request);
      }
      else
         //terminate the discover process.
         scif_sas_smp_remote_device_fail_target_reset(fw_device, fw_request);
   }
   else if (fw_device->protocol_device.smp_device.current_activity ==
      SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_SATA_SPINUP_HOLD_RELEASE)
   {
      SCIF_SAS_REMOTE_DEVICE_T * target_device =
         scif_sas_domain_get_device_by_containing_device(
            fw_device->domain,
            fw_device,
            fw_device->protocol_device.smp_device.current_activity_phy_index
         );

      if (status == SCI_SUCCESS)
      {
         //move on to next round of SPINUP_HOLD_REALSE activity.
         scif_sas_smp_remote_device_sata_spinup_hold_release(fw_device);
      }
      else if (status == SCI_FAILURE_RETRY_REQUIRED)
      {
         U32 delay =
            (scic_remote_device_get_suggested_reset_timeout(target_device->core_object) /
                SCIF_SAS_IO_RETRY_LIMIT);

         //Retry the smp request. Since we are in the middle of Discover
         //process, all the smp requests are internal. A new smp request
         //will be created for retry.
         if (io_retry_count < SCIF_SAS_IO_RETRY_LIMIT)
         {
            scif_sas_smp_remote_device_retry_internal_io(
               fw_device, io_retry_count, delay);
         }
         else //give up on this target device.
         {
            scif_sas_smp_remote_device_fail_target_spinup_hold_release(
               fw_device , target_device);
         }
      }
      else //give up on this target device.
        scif_sas_smp_remote_device_fail_target_spinup_hold_release(
           fw_device, target_device);
   }
   else if (fw_device->protocol_device.smp_device.current_activity ==
      SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_CONFIG_ROUTE_TABLE)
   {
      SCI_FAST_LIST_ELEMENT_T * next_phy_element = sci_fast_list_get_next(
         &(fw_device->protocol_device.smp_device.curr_config_route_destination_smp_phy->list_element) );

      SCI_FAST_LIST_T * destination_smp_phy_list =
          fw_device->protocol_device.smp_device.curr_config_route_destination_smp_phy->list_element.owning_list;

      SCIF_SAS_SMP_PHY_T * next_phy_in_wide_port = NULL;

      if (next_phy_element != NULL
          && status != SCI_FAILURE_EXCEED_MAX_ROUTE_INDEX)
      {
         fw_device->protocol_device.smp_device.curr_config_route_index++;

         fw_device->protocol_device.smp_device.curr_config_route_destination_smp_phy =
            (SCIF_SAS_SMP_PHY_T *)sci_fast_list_get_object(next_phy_element);

         // Update the anchor for config route index.
         fw_device->protocol_device.smp_device.config_route_smp_phy_anchor->config_route_table_index_anchor =
            fw_device->protocol_device.smp_device.curr_config_route_index;

         scif_sas_smp_remote_device_configure_route_table(fw_device);
      }
      else if ( scif_sas_smp_remote_device_get_config_route_table_method(fw_device)
                   == SCIF_SAS_CONFIG_ROUTE_TABLE_ALL_PHYS
                && (next_phy_in_wide_port = scif_sas_smp_phy_find_next_phy_in_wide_port(
                       fw_device->protocol_device.smp_device.config_route_smp_phy_anchor)
                   )!= NULL
              )
      {
         //config the other phy in the same wide port
         fw_device->protocol_device.smp_device.config_route_smp_phy_anchor =
            next_phy_in_wide_port;

         fw_device->protocol_device.smp_device.current_activity_phy_index =
            fw_device->protocol_device.smp_device.config_route_smp_phy_anchor->phy_identifier;

         fw_device->protocol_device.smp_device.curr_config_route_destination_smp_phy =
            sci_fast_list_get_head(destination_smp_phy_list);

         if (fw_device->protocol_device.smp_device.config_route_smp_phy_anchor->config_route_table_index_anchor != 0)
            fw_device->protocol_device.smp_device.curr_config_route_index =
               fw_device->protocol_device.smp_device.config_route_smp_phy_anchor->config_route_table_index_anchor + 1;
         else
            fw_device->protocol_device.smp_device.curr_config_route_index = 0;

         scif_sas_smp_remote_device_configure_route_table(fw_device);
      }
      else if ( fw_device->protocol_device.smp_device.is_route_table_cleaned == FALSE)
      {
         fw_device->protocol_device.smp_device.current_activity =
            SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_CLEAN_ROUTE_TABLE;

         scif_sas_smp_remote_device_clean_route_table(fw_device);
      }
      else
      {
         //set this device's activity to NON.
         fw_device->protocol_device.smp_device.current_activity =
            SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_NONE;

         //we need to notify domain that this device finished config route table, domain
         //may pick up other activities (i.e. Discover) for other expanders.
         scif_sas_domain_continue_discover(fw_device->domain);
      }
   }
   else if (fw_device->protocol_device.smp_device.current_activity ==
               SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_CLEAN_ROUTE_TABLE)
   {
      scif_sas_smp_remote_device_clean_route_table(fw_device);
   }
   else if (fw_device->protocol_device.smp_device.current_activity ==
               SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_CLEAR_AFFILIATION)
   {
      scif_sas_smp_remote_device_continue_clear_affiliation(fw_device);
   }
}