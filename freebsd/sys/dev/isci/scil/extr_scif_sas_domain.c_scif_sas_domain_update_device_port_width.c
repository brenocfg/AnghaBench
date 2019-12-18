#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U8 ;
struct TYPE_13__ {int /*<<< orphan*/  sas_address; } ;
struct TYPE_16__ {int /*<<< orphan*/  phy_mask; TYPE_3__ remote; } ;
struct TYPE_15__ {int /*<<< orphan*/  core_object; } ;
struct TYPE_11__ {scalar_t__ attached_ssp_target; } ;
struct TYPE_12__ {TYPE_1__ bits; } ;
struct TYPE_14__ {TYPE_2__ u; } ;
typedef  TYPE_4__ SMP_DISCOVER_RESPONSE_PROTOCOLS_T ;
typedef  int /*<<< orphan*/  SCI_PORT_HANDLE_T ;
typedef  TYPE_5__ SCIF_SAS_REMOTE_DEVICE_T ;
typedef  int /*<<< orphan*/  SCIF_SAS_DOMAIN_T ;
typedef  TYPE_6__ SCIC_PORT_PROPERTIES_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_LOG_OBJECT_DOMAIN ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCI_GET_BITS_SET_COUNT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* SCI_INVALID_HANDLE ; 
 int /*<<< orphan*/  sci_base_object_get_logger (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_port_get_properties (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  scic_remote_device_get_protocols (int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ scif_domain_get_device_by_sas_address (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scif_sas_remote_device_update_port_width (TYPE_5__*,int /*<<< orphan*/ ) ; 

void scif_sas_domain_update_device_port_width(
   SCIF_SAS_DOMAIN_T * fw_domain,
   SCI_PORT_HANDLE_T   port
)
{
   SCIF_SAS_REMOTE_DEVICE_T * fw_device;
   SCIC_PORT_PROPERTIES_T     properties;
   U8                         new_port_width = 0;

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_domain),
      SCIF_LOG_OBJECT_DOMAIN,
      "scif_sas_domain_update_device_port_width(0x%x, 0x%x) enter\n",
      fw_domain, port
   ));

   scic_port_get_properties(port, &properties);

   fw_device = (SCIF_SAS_REMOTE_DEVICE_T *)
                  scif_domain_get_device_by_sas_address(
                  fw_domain, &properties.remote.sas_address
               );

   // If the device already existed in the domain, it is a wide port SSP target,
   // we need to update its port width.
   if (fw_device != SCI_INVALID_HANDLE)
   {
      SMP_DISCOVER_RESPONSE_PROTOCOLS_T  dev_protocols;
      scic_remote_device_get_protocols(fw_device->core_object, &dev_protocols);

      if (dev_protocols.u.bits.attached_ssp_target)
      {
         //Get accurate port width from port's phy mask for a DA device.
         SCI_GET_BITS_SET_COUNT(properties.phy_mask, new_port_width);

         scif_sas_remote_device_update_port_width(fw_device, new_port_width);
      }
   }
}