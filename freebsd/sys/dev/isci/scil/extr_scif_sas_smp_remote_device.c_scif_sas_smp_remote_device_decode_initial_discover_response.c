#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_46__   TYPE_9__ ;
typedef  struct TYPE_45__   TYPE_8__ ;
typedef  struct TYPE_44__   TYPE_7__ ;
typedef  struct TYPE_43__   TYPE_6__ ;
typedef  struct TYPE_42__   TYPE_5__ ;
typedef  struct TYPE_41__   TYPE_4__ ;
typedef  struct TYPE_40__   TYPE_3__ ;
typedef  struct TYPE_39__   TYPE_2__ ;
typedef  struct TYPE_38__   TYPE_1__ ;
typedef  struct TYPE_37__   TYPE_15__ ;
typedef  struct TYPE_36__   TYPE_14__ ;
typedef  struct TYPE_35__   TYPE_13__ ;
typedef  struct TYPE_34__   TYPE_12__ ;
typedef  struct TYPE_33__   TYPE_11__ ;
typedef  struct TYPE_32__   TYPE_10__ ;

/* Type definitions */
struct TYPE_46__ {int /*<<< orphan*/  current_smp_request; int /*<<< orphan*/  scheduled_activity; } ;
struct TYPE_43__ {int attached_stp_target; scalar_t__ attached_sata_device; scalar_t__ attached_smp_target; scalar_t__ attached_ssp_target; } ;
struct TYPE_44__ {TYPE_6__ bits; } ;
struct TYPE_45__ {TYPE_7__ u; } ;
struct TYPE_41__ {scalar_t__ negotiated_physical_link_rate; } ;
struct TYPE_42__ {TYPE_4__ sas2; } ;
struct TYPE_39__ {scalar_t__ attached_device_type; scalar_t__ negotiated_physical_link_rate; } ;
struct TYPE_40__ {TYPE_2__ sas1_1; } ;
struct TYPE_35__ {TYPE_8__ protocols; int /*<<< orphan*/  phy_identifier; TYPE_5__ u4; TYPE_3__ u2; int /*<<< orphan*/  attached_sas_address; } ;
struct TYPE_38__ {TYPE_13__ discover; } ;
struct TYPE_37__ {int /*<<< orphan*/  controller; } ;
struct TYPE_32__ {TYPE_9__ smp_device; } ;
struct TYPE_36__ {scalar_t__ is_currently_discovered; scalar_t__ device_port_width; TYPE_10__ protocol_device; struct TYPE_36__* containing_device; int /*<<< orphan*/  core_object; TYPE_15__* domain; } ;
struct TYPE_34__ {scalar_t__ function_result; } ;
struct TYPE_33__ {TYPE_12__ header; TYPE_1__ response; } ;
typedef  TYPE_11__ SMP_RESPONSE_T ;
typedef  TYPE_12__ SMP_RESPONSE_HEADER_T ;
typedef  TYPE_13__ SMP_RESPONSE_DISCOVER_T ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_SAS_ADDRESS_T ;
typedef  TYPE_14__ SCIF_SAS_REMOTE_DEVICE_T ;
typedef  TYPE_15__ SCIF_SAS_DOMAIN_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_LOG_ERROR (int /*<<< orphan*/ ) ; 
 int SCIF_LOG_OBJECT_DOMAIN_DISCOVERY ; 
 int SCIF_LOG_OBJECT_REMOTE_DEVICE ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_DISCOVER ; 
 int /*<<< orphan*/  SCI_FAILURE ; 
 TYPE_14__* SCI_INVALID_HANDLE ; 
 scalar_t__ SCI_SATA_SPINUP_HOLD ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  SMP_FUNCTION_PHY_CONTROL ; 
 int /*<<< orphan*/  SMP_FUNCTION_REPORT_PHY_SATA ; 
 scalar_t__ SMP_NO_DEVICE_ATTACHED ; 
 scalar_t__ SMP_RESULT_FUNCTION_ACCEPTED ; 
 scalar_t__ SMP_RESULT_PHY_VACANT ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_14__*) ; 
 scalar_t__ scic_remote_device_get_port_width (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_cb_domain_device_removed (int /*<<< orphan*/ ,TYPE_15__*,TYPE_14__*) ; 
 int /*<<< orphan*/  scif_cb_domain_ea_device_added (int /*<<< orphan*/ ,TYPE_15__*,TYPE_14__*,TYPE_13__*) ; 
 scalar_t__ scif_domain_get_device_by_sas_address (TYPE_15__*,int /*<<< orphan*/ *) ; 
 TYPE_14__* scif_sas_domain_get_device_by_containing_device (TYPE_15__*,TYPE_14__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_sas_remote_device_update_port_width (TYPE_14__*,scalar_t__) ; 
 int /*<<< orphan*/  scif_sas_smp_remote_device_save_smp_phy_info (TYPE_14__*,TYPE_13__*) ; 

SCI_STATUS scif_sas_smp_remote_device_decode_initial_discover_response(
   SCIF_SAS_REMOTE_DEVICE_T * fw_device,
   SMP_RESPONSE_T           * smp_response
)
{
   SCIF_SAS_DOMAIN_T        * fw_domain = fw_device->domain;
   SCI_SAS_ADDRESS_T          attached_device_address;
   SCIF_SAS_REMOTE_DEVICE_T * attached_remote_device;
   SMP_RESPONSE_DISCOVER_T  * discover_response =
      &smp_response->response.discover;
   SMP_RESPONSE_HEADER_T    * response_header = &smp_response->header;

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_device),
      SCIF_LOG_OBJECT_REMOTE_DEVICE | SCIF_LOG_OBJECT_DOMAIN_DISCOVERY,
      "scif_sas_smp_remote_device_decode_initial_discover_response(0x%x, 0x%x) enter\n",
      fw_device, smp_response
   ));

   if (response_header->function_result == SMP_RESULT_PHY_VACANT)
   {
      return SCI_SUCCESS;
   }
   else if (response_header->function_result != SMP_RESULT_FUNCTION_ACCEPTED)
   {
      /// @todo: more decoding work needed when the function_result is not
      /// SMP_RESULT_FUNCTION_ACCEPTED. Retry might be the option for some
      /// function result.
      SCIF_LOG_ERROR((
         sci_base_object_get_logger(fw_device),
         SCIF_LOG_OBJECT_REMOTE_DEVICE | SCIF_LOG_OBJECT_DOMAIN_DISCOVERY,
         "Discover function result(0x%x)\n",
         response_header->function_result
      ));

      return SCI_FAILURE;
   }

   //only if there is target device attached. We don't add device that is
   //initiator only.
   if ( ( discover_response->u2.sas1_1.attached_device_type
             != SMP_NO_DEVICE_ATTACHED )
       && ( discover_response->protocols.u.bits.attached_ssp_target
           || discover_response->protocols.u.bits.attached_stp_target
           || discover_response->protocols.u.bits.attached_smp_target
           || discover_response->protocols.u.bits.attached_sata_device ) )
   {
      attached_device_address = discover_response->attached_sas_address;

      attached_remote_device = (SCIF_SAS_REMOTE_DEVICE_T *)
         scif_domain_get_device_by_sas_address(
            fw_domain, &attached_device_address
         );

      //need to check if the device already existed in the domian.
      if (attached_remote_device != SCI_INVALID_HANDLE)
      {
#if !defined(DISABLE_WIDE_PORTED_TARGETS)
         if ( attached_remote_device->is_currently_discovered == TRUE
             && attached_remote_device != fw_device->containing_device )
         {
            //a downstream wide port target is found.
            attached_remote_device->device_port_width++;
         }
         else
#endif //#if !defined(DISABLE_WIDE_PORTED_TARGETS)
         {
            //The device already existed. Mark the device as discovered.
            attached_remote_device->is_currently_discovered = TRUE;
         }

#if !defined(DISABLE_WIDE_PORTED_TARGETS)
         if (attached_remote_device->device_port_width !=
                scic_remote_device_get_port_width(attached_remote_device->core_object)
             && discover_response->protocols.u.bits.attached_ssp_target
            )
         {
            scif_sas_remote_device_update_port_width(
               attached_remote_device, attached_remote_device->device_port_width);
         }
#endif //#if !defined(DISABLE_WIDE_PORTED_TARGETS)

         if ( discover_response->protocols.u.bits.attached_smp_target
             && attached_remote_device != fw_device->containing_device)
         {
            //another expander device is discovered. Its own smp discover will starts after
            //this discover finishes.
            attached_remote_device->protocol_device.smp_device.scheduled_activity =
               SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_DISCOVER;
         }
      }
      else
      {
         //report the discovery of a disk for all types of end device.
         scif_cb_domain_ea_device_added(
            fw_domain->controller, fw_domain, fw_device, discover_response
         );

         //get info from discover response to see what we found. And do
         //extra work according to end device's protocol type.
         if ( discover_response->protocols.u.bits.attached_ssp_target
             || discover_response->protocols.u.bits.attached_smp_target)
         {
            //for SSP or SMP target, no extra work.
            ;
         }
         else if (  (discover_response->protocols.u.bits.attached_stp_target)
                 || (discover_response->protocols.u.bits.attached_sata_device) )
         {
            // We treat a SATA Device bit the same as an attached STP
            // target.
            discover_response->protocols.u.bits.attached_stp_target = 1;

            //kick off REPORT PHY SATA to the same phy.
            fw_device->protocol_device.smp_device.current_smp_request =
               SMP_FUNCTION_REPORT_PHY_SATA;
         }
      }
   }
   else if( (discover_response->u2.sas1_1.negotiated_physical_link_rate == SCI_SATA_SPINUP_HOLD
             || discover_response->u4.sas2.negotiated_physical_link_rate == SCI_SATA_SPINUP_HOLD)
          &&(discover_response->protocols.u.bits.attached_stp_target
             || discover_response->protocols.u.bits.attached_sata_device)
          )
   {
      attached_remote_device = scif_sas_domain_get_device_by_containing_device(
                                  fw_domain,
                                  fw_device,
                                  discover_response->phy_identifier
                               );

      if (attached_remote_device != SCI_INVALID_HANDLE)
      {
         //Here, the only reason a device already existed in domain but
         //the initial discover rersponse shows it in SPINUP_HOLD, is that
         //a device has been removed and coming back in SPINUP_HOLD before
         //we detected. The possibility of this situation is very very rare.
         //we need to remove the device then add it back using the new
         //discover response.
         scif_cb_domain_device_removed(
            fw_domain->controller, fw_domain, attached_remote_device
         );
      }

      discover_response->protocols.u.bits.attached_stp_target = 1;

      //still report ea_device_added(). But this device will not be
      //started during scif_remote_device_ea_construct().
      scif_cb_domain_ea_device_added(
         fw_domain->controller, fw_domain, fw_device, discover_response
      );

      //need to send Phy Control (RESET) to release the phy from spinup hold
      //condition.
      fw_device->protocol_device.smp_device.current_smp_request =
         SMP_FUNCTION_PHY_CONTROL;
   }

   //update the smp phy info based on this DISCOVER response.
   return scif_sas_smp_remote_device_save_smp_phy_info(
             fw_device, discover_response);
}