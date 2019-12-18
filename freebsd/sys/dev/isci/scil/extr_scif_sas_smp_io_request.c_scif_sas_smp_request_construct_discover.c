#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U8 ;
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_6__ {int /*<<< orphan*/  phy_identifier; } ;
struct TYPE_7__ {TYPE_1__ discover; } ;
struct TYPE_8__ {TYPE_2__ request; } ;
typedef  int /*<<< orphan*/  SMP_RESPONSE_DISCOVER_T ;
typedef  TYPE_3__ SMP_REQUEST_T ;
typedef  int /*<<< orphan*/  SMP_REQUEST_PHY_IDENTIFIER_T ;
typedef  int /*<<< orphan*/  SCIF_SAS_REMOTE_DEVICE_T ;
typedef  int /*<<< orphan*/  SCIF_SAS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_LOG_INFO (int /*<<< orphan*/ ) ; 
 int SCIF_LOG_OBJECT_DOMAIN_DISCOVERY ; 
 int SCIF_LOG_OBJECT_IO_REQUEST ; 
 int /*<<< orphan*/  SMP_FUNCTION_DISCOVER ; 
 int /*<<< orphan*/  sci_base_object_get_logger (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scif_sas_smp_protocol_request_construct (TYPE_3__*,int /*<<< orphan*/ ,int,int) ; 
 void* scif_sas_smp_request_build (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,void*,void*) ; 

void * scif_sas_smp_request_construct_discover(
   SCIF_SAS_CONTROLLER_T    * fw_controller,
   SCIF_SAS_REMOTE_DEVICE_T * fw_device,
   U8                         phy_identifier,
   void                     * external_request_object,
   void                     * external_memory
)
{
   SMP_REQUEST_T smp_discover;

   scif_sas_smp_protocol_request_construct(
      &smp_discover,
      SMP_FUNCTION_DISCOVER,
      sizeof(SMP_RESPONSE_DISCOVER_T) / sizeof(U32),
      sizeof(SMP_REQUEST_PHY_IDENTIFIER_T) / sizeof(U32)
   );

   smp_discover.request.discover.phy_identifier = phy_identifier;

   SCIF_LOG_INFO((
      sci_base_object_get_logger(fw_device),
      SCIF_LOG_OBJECT_IO_REQUEST | SCIF_LOG_OBJECT_DOMAIN_DISCOVERY,
      "SMP DISCOVER - Device:0x%x PhyId:0x%x\n",
      fw_device, phy_identifier
   ));

   return scif_sas_smp_request_build(
             fw_controller, fw_device, &smp_discover,
             external_request_object, external_memory
          );
}