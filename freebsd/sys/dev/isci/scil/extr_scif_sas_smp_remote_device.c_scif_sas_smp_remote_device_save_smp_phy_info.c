#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  smp_device; } ;
struct TYPE_26__ {struct TYPE_26__* containing_device; int /*<<< orphan*/  domain; TYPE_1__ protocol_device; } ;
struct TYPE_23__ {int /*<<< orphan*/  attached_phy; } ;
struct TYPE_25__ {TYPE_5__ u; } ;
struct TYPE_20__ {scalar_t__ attached_smp_target; } ;
struct TYPE_21__ {TYPE_2__ bits; } ;
struct TYPE_22__ {TYPE_3__ u; } ;
struct TYPE_24__ {int /*<<< orphan*/  attached_phy_identifier; TYPE_4__ protocols; int /*<<< orphan*/  attached_sas_address; int /*<<< orphan*/  phy_identifier; } ;
typedef  TYPE_6__ SMP_RESPONSE_DISCOVER_T ;
typedef  scalar_t__ SCI_STATUS ;
typedef  TYPE_7__ SCIF_SAS_SMP_PHY_T ;
typedef  TYPE_8__ SCIF_SAS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int SCIF_LOG_OBJECT_DOMAIN_DISCOVERY ; 
 int SCIF_LOG_OBJECT_REMOTE_DEVICE ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ SCI_FAILURE_ILLEGAL_ROUTING_ATTRIBUTE_CONFIGURATION ; 
 scalar_t__ SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_8__*) ; 
 scalar_t__ scif_domain_get_device_by_sas_address (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scif_sas_smp_phy_save_information (TYPE_7__*,TYPE_8__*,TYPE_6__*) ; 
 scalar_t__ scif_sas_smp_phy_set_attached_phy (TYPE_7__*,int /*<<< orphan*/ ,TYPE_8__*) ; 
 scalar_t__ scif_sas_smp_phy_verify_routing_attribute (TYPE_7__*,int /*<<< orphan*/ ) ; 
 TYPE_7__* scif_sas_smp_remote_device_find_smp_phy_by_id (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

SCI_STATUS scif_sas_smp_remote_device_save_smp_phy_info(
   SCIF_SAS_REMOTE_DEVICE_T * fw_device,
   SMP_RESPONSE_DISCOVER_T  * discover_response
)
{
   SCI_STATUS status = SCI_SUCCESS;
   SCIF_SAS_SMP_PHY_T * smp_phy = NULL;
   SCIF_SAS_REMOTE_DEVICE_T * attached_device = NULL;

    SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_device),
      SCIF_LOG_OBJECT_REMOTE_DEVICE | SCIF_LOG_OBJECT_DOMAIN_DISCOVERY,
      "scif_sas_smp_remote_device_save_smp_phy_info(0x%x, 0x%x) enter\n",
      fw_device, discover_response
   ));

   smp_phy = scif_sas_smp_remote_device_find_smp_phy_by_id(
                discover_response->phy_identifier,
                &fw_device->protocol_device.smp_device
             );

   ASSERT( smp_phy != NULL );

   //Note, attached_device could be NULL, not all the smp phy have to connected to a device.
   attached_device = (SCIF_SAS_REMOTE_DEVICE_T *)
      scif_domain_get_device_by_sas_address(
         fw_device->domain, &discover_response->attached_sas_address);

   scif_sas_smp_phy_save_information(
      smp_phy, attached_device, discover_response);

   //handle the special case of smp phys between expanders.
   if ( discover_response->protocols.u.bits.attached_smp_target )
   {
       //this fw_device is a child expander, just found its parent expander.
       //And there is no smp_phy constructed yet, record this phy connection.
       if ( attached_device != NULL
           && attached_device == fw_device->containing_device )
       {
          //record the smp phy info, for this phy connects to a upstream smp device.
          //the connection of a pair of smp phys are completed.
          status = scif_sas_smp_phy_set_attached_phy(
                      smp_phy,
                      discover_response->attached_phy_identifier,
                      attached_device
                   );

          if (status == SCI_SUCCESS)
          {
             //check the routing attribute for this phy and its containing device's
             //expander_phy_routing_attribute.
             if ( scif_sas_smp_phy_verify_routing_attribute(
                     smp_phy, smp_phy->u.attached_phy) != SCI_SUCCESS )
                return SCI_FAILURE_ILLEGAL_ROUTING_ATTRIBUTE_CONFIGURATION;
          }
       }
    }

    return status;
}