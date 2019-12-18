#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_15__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
struct TYPE_30__ {TYPE_15__* domain; int /*<<< orphan*/  parent; TYPE_6__* state_handlers; int /*<<< orphan*/  core_object; int /*<<< orphan*/  device_port_width; } ;
struct TYPE_29__ {scalar_t__ low; scalar_t__ high; } ;
struct TYPE_24__ {scalar_t__ smp_target; scalar_t__ stp_target; } ;
struct TYPE_25__ {TYPE_3__ bits; } ;
struct TYPE_28__ {TYPE_4__ u; } ;
struct TYPE_26__ {scalar_t__ (* start_handler ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_27__ {TYPE_5__ parent; } ;
struct TYPE_22__ {scalar_t__ low; scalar_t__ high; } ;
struct TYPE_23__ {TYPE_1__ sas_address; } ;
struct TYPE_21__ {int /*<<< orphan*/  remote_device_list; int /*<<< orphan*/  core_object; } ;
struct TYPE_20__ {int /*<<< orphan*/  phy_mask; TYPE_2__ remote; } ;
typedef  scalar_t__ SCI_STATUS ;
typedef  TYPE_7__ SCI_SAS_IDENTIFY_ADDRESS_FRAME_PROTOCOLS_T ;
typedef  TYPE_8__ SCI_SAS_ADDRESS_T ;
typedef  scalar_t__ SCI_REMOTE_DEVICE_HANDLE_T ;
typedef  TYPE_9__ SCIF_SAS_REMOTE_DEVICE_T ;
typedef  TYPE_10__ SCIC_PORT_PROPERTIES_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_LOG_INFO (int /*<<< orphan*/ ) ; 
 int SCIF_LOG_OBJECT_DOMAIN_DISCOVERY ; 
 int SCIF_LOG_OBJECT_REMOTE_DEVICE ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIF_LOG_WARNING (int /*<<< orphan*/ ) ; 
 scalar_t__ SCI_FAILURE_DEVICE_EXISTS ; 
 scalar_t__ SCI_FAILURE_UNSUPPORTED_PROTOCOL ; 
 int /*<<< orphan*/  SCI_GET_BITS_SET_COUNT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SCI_INVALID_HANDLE ; 
 scalar_t__ SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_abstract_list_pushback (int /*<<< orphan*/ *,TYPE_9__*) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_9__*) ; 
 int /*<<< orphan*/  scic_port_get_properties (int /*<<< orphan*/ ,TYPE_10__*) ; 
 scalar_t__ scic_remote_device_da_construct (int /*<<< orphan*/ ) ; 
 scalar_t__ scif_domain_get_device_by_sas_address (TYPE_15__*,TYPE_8__*) ; 
 int /*<<< orphan*/  scif_sas_smp_remote_device_construct (TYPE_9__*) ; 
 int /*<<< orphan*/  scif_sas_stp_remote_device_construct (TYPE_9__*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *) ; 

SCI_STATUS scif_remote_device_da_construct(
   SCI_REMOTE_DEVICE_HANDLE_T                   remote_device,
   SCI_SAS_ADDRESS_T                          * sas_address,
   SCI_SAS_IDENTIFY_ADDRESS_FRAME_PROTOCOLS_T * protocols
)
{
   SCI_STATUS                 status    = SCI_SUCCESS;
   SCIF_SAS_REMOTE_DEVICE_T * fw_device = (SCIF_SAS_REMOTE_DEVICE_T *)
                                          remote_device;

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_device),
      SCIF_LOG_OBJECT_REMOTE_DEVICE,
      "scif_remote_device_da_construct(0x%x, 0x%x, 0x%x) enter\n",
      remote_device, sas_address, protocols
   ));

   // Make sure the device hasn't already been constructed and added
   // to the domain.
   if (scif_domain_get_device_by_sas_address(fw_device->domain, sas_address)
       == SCI_INVALID_HANDLE)
   {
      SCIC_PORT_PROPERTIES_T  properties;

      scic_port_get_properties(fw_device->domain->core_object, &properties);

      // Check to see if this is the direct attached device.
      if (  (sas_address->low == properties.remote.sas_address.low)
         && (sas_address->high == properties.remote.sas_address.high) )
      {
         //Get accurate port width from port's phy mask for a DA device.
         SCI_GET_BITS_SET_COUNT(properties.phy_mask, fw_device->device_port_width);

         status = scic_remote_device_da_construct(fw_device->core_object);
      }
      else
         // Don't allow the user to construct a direct attached device
         // if it's not a direct attached device.
         status = SCI_FAILURE_UNSUPPORTED_PROTOCOL;
   }
   else
      status = SCI_FAILURE_DEVICE_EXISTS;

   if (status == SCI_SUCCESS)
   {
      // Add the device to the domain list.
      sci_abstract_list_pushback(
         &fw_device->domain->remote_device_list, fw_device
      );

      // If a SATA/STP device is connected, then construct it.
      if (protocols->u.bits.stp_target)
         scif_sas_stp_remote_device_construct(fw_device);
      else if (protocols->u.bits.smp_target)
         scif_sas_smp_remote_device_construct(fw_device);

      SCIF_LOG_INFO((
         sci_base_object_get_logger(fw_device),
         SCIF_LOG_OBJECT_REMOTE_DEVICE | SCIF_LOG_OBJECT_DOMAIN_DISCOVERY,
         "Domain:0x%x SasAddress:0x%x,0x%x remote device constructed\n",
         fw_device->domain, sas_address->low, sas_address->high
      ));

      status = fw_device->state_handlers->parent.start_handler(
                  &fw_device->parent
               );
   }
   else
   {
      SCIF_LOG_WARNING((
         sci_base_object_get_logger(fw_device),
         SCIF_LOG_OBJECT_REMOTE_DEVICE | SCIF_LOG_OBJECT_DOMAIN_DISCOVERY,
         "Domain:0x%x SasAddress:0x%x,0x%x Status:0x%x remote device construct failure\n",
         fw_device->domain, sas_address->low, sas_address->high, status
      ));
   }

   return status;
}