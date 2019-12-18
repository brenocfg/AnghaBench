#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  current_smp_request; } ;
struct TYPE_11__ {TYPE_1__ smp_device; } ;
struct TYPE_15__ {TYPE_2__ protocol_device; } ;
struct TYPE_14__ {scalar_t__ function_result; } ;
struct TYPE_12__ {int /*<<< orphan*/  report_phy_sata; } ;
struct TYPE_13__ {TYPE_5__ header; TYPE_3__ response; } ;
typedef  TYPE_4__ SMP_RESPONSE_T ;
typedef  int /*<<< orphan*/  SMP_RESPONSE_REPORT_PHY_SATA_T ;
typedef  TYPE_5__ SMP_RESPONSE_HEADER_T ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  TYPE_6__ SCIF_SAS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_LOG_ERROR (int /*<<< orphan*/ ) ; 
 int SCIF_LOG_OBJECT_DOMAIN_DISCOVERY ; 
 int SCIF_LOG_OBJECT_REMOTE_DEVICE ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCI_FAILURE ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  SMP_FUNCTION_DISCOVER ; 
 scalar_t__ SMP_RESULT_FUNCTION_ACCEPTED ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_6__*) ; 
 int /*<<< orphan*/  scif_sas_remote_device_save_report_phy_sata_information (int /*<<< orphan*/ *) ; 

SCI_STATUS scif_sas_smp_remote_device_decode_report_phy_sata_response(
   SCIF_SAS_REMOTE_DEVICE_T * fw_device,
   SMP_RESPONSE_T           * smp_response
)
{
   SMP_RESPONSE_REPORT_PHY_SATA_T * report_phy_sata_response =
      &smp_response->response.report_phy_sata;

   SMP_RESPONSE_HEADER_T * response_header = &smp_response->header;

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_device),
      SCIF_LOG_OBJECT_REMOTE_DEVICE | SCIF_LOG_OBJECT_DOMAIN_DISCOVERY,
      "scif_sas_smp_remote_device_decode_report_phy_sata_response(0x%x, 0x%x) enter\n",
      fw_device, smp_response
   ));

   if (response_header->function_result != SMP_RESULT_FUNCTION_ACCEPTED)
   {
      /// @todo: more decoding work needed when the function_result is not
      /// SMP_RESULT_FUNCTION_ACCEPTED. Retry might be the option for some
      /// function result.
      SCIF_LOG_ERROR((
         sci_base_object_get_logger(fw_device),
         SCIF_LOG_OBJECT_REMOTE_DEVICE | SCIF_LOG_OBJECT_DOMAIN_DISCOVERY,
         "Report Phy Sata function result(0x%x)\n",
         response_header->function_result
      ));

      return SCI_FAILURE;
   }

   scif_sas_remote_device_save_report_phy_sata_information(
      report_phy_sata_response
   );

   // continue the discover process.
   fw_device->protocol_device.smp_device.current_smp_request =
      SMP_FUNCTION_DISCOVER;

   return SCI_SUCCESS;
}