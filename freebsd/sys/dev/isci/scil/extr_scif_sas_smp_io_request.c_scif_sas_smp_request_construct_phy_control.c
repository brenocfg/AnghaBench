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
typedef  void* U8 ;
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_6__ {void* phy_identifier; void* phy_operation; } ;
struct TYPE_7__ {TYPE_1__ phy_control; } ;
struct TYPE_8__ {TYPE_2__ request; } ;
typedef  TYPE_3__ SMP_REQUEST_T ;
typedef  int /*<<< orphan*/  SMP_REQUEST_PHY_CONTROL_T ;
typedef  int /*<<< orphan*/  SCIF_SAS_REMOTE_DEVICE_T ;
typedef  int /*<<< orphan*/  SCIF_SAS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  SMP_FUNCTION_PHY_CONTROL ; 
 int /*<<< orphan*/  scif_sas_smp_protocol_request_construct (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* scif_sas_smp_request_build (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,void*,void*) ; 

void * scif_sas_smp_request_construct_phy_control(
   SCIF_SAS_CONTROLLER_T    * fw_controller,
   SCIF_SAS_REMOTE_DEVICE_T * fw_device,
   U8                         phy_operation,
   U8                         phy_identifier,
   void                     * external_request_object,
   void                     * external_memory
)
{
   SMP_REQUEST_T phy_control;

   scif_sas_smp_protocol_request_construct(
      &phy_control,
      SMP_FUNCTION_PHY_CONTROL,
      0,
      sizeof(SMP_REQUEST_PHY_CONTROL_T) / sizeof(U32)
   );

   phy_control.request.phy_control.phy_operation = phy_operation;
   phy_control.request.phy_control.phy_identifier = phy_identifier;

   return scif_sas_smp_request_build(
             fw_controller, fw_device, &phy_control,
             external_request_object, external_memory
          );
}