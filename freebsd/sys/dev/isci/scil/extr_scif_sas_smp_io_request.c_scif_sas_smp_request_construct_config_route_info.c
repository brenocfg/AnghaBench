#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct SCIF_SAS_REMOTE_DEVICE {int dummy; } ;
struct SCIF_SAS_CONTROLLER {int dummy; } ;
typedef  int /*<<< orphan*/  U8 ;
typedef  int /*<<< orphan*/  U32 ;
typedef  int U16 ;
struct TYPE_11__ {int /*<<< orphan*/  low; int /*<<< orphan*/  high; } ;
struct TYPE_8__ {int expander_route_index_high; int expander_route_index; int disable_route_entry; int /*<<< orphan*/ * routed_sas_address; int /*<<< orphan*/  phy_identifier; } ;
struct TYPE_9__ {TYPE_1__ configure_route_information; } ;
struct TYPE_10__ {TYPE_2__ request; } ;
typedef  TYPE_3__ SMP_REQUEST_T ;
typedef  int /*<<< orphan*/  SMP_REQUEST_CONFIGURE_ROUTE_INFORMATION_T ;
typedef  TYPE_4__ SCI_SAS_ADDRESS_T ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  SMP_FUNCTION_CONFIGURE_ROUTE_INFORMATION ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  scif_sas_smp_protocol_request_construct (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* scif_sas_smp_request_build (struct SCIF_SAS_CONTROLLER*,struct SCIF_SAS_REMOTE_DEVICE*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void * scif_sas_smp_request_construct_config_route_info(
   struct SCIF_SAS_CONTROLLER    * fw_controller,
   struct SCIF_SAS_REMOTE_DEVICE * fw_device,
   U8                              phy_id,
   U16                             route_index,
   SCI_SAS_ADDRESS_T               destination_sas_address,
   BOOL                            disable_expander_route_entry
)
{
   SMP_REQUEST_T config_route_info;

   scif_sas_smp_protocol_request_construct(
      &config_route_info,
      SMP_FUNCTION_CONFIGURE_ROUTE_INFORMATION,
      0,
      sizeof(SMP_REQUEST_CONFIGURE_ROUTE_INFORMATION_T) / sizeof(U32)
   );

   config_route_info.request.configure_route_information.phy_identifier = phy_id;
   config_route_info.request.configure_route_information.expander_route_index_high =
      ((route_index & 0xff00) >> 8);
   config_route_info.request.configure_route_information.expander_route_index =
      route_index & 0xff;
   config_route_info.request.configure_route_information.routed_sas_address[0] =
      destination_sas_address.high;
   config_route_info.request.configure_route_information.routed_sas_address[1] =
      destination_sas_address.low;

   if (disable_expander_route_entry == TRUE)
      config_route_info.request.configure_route_information.disable_route_entry = 1;

   return scif_sas_smp_request_build(
             fw_controller, fw_device, &config_route_info,
             NULL, NULL
          );
}