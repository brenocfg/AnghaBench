#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  current_smp_request; } ;
struct TYPE_9__ {TYPE_2__ smp_device; } ;
struct TYPE_13__ {TYPE_1__ protocol_device; } ;
struct TYPE_12__ {scalar_t__ function_result; } ;
struct TYPE_11__ {TYPE_4__ header; } ;
typedef  TYPE_3__ SMP_RESPONSE_T ;
typedef  TYPE_4__ SMP_RESPONSE_HEADER_T ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  TYPE_5__ SCIF_SAS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_LOG_ERROR (int /*<<< orphan*/ ) ; 
 int SCIF_LOG_OBJECT_DOMAIN_DISCOVERY ; 
 int SCIF_LOG_OBJECT_REMOTE_DEVICE ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCI_FAILURE_RETRY_REQUIRED ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  SMP_FUNCTION_DISCOVER ; 
 scalar_t__ SMP_RESULT_FUNCTION_ACCEPTED ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_5__*) ; 

SCI_STATUS scif_sas_smp_remote_device_decode_discover_phy_control_response(
   SCIF_SAS_REMOTE_DEVICE_T * fw_device,
   SMP_RESPONSE_T           * smp_response
)
{
   SMP_RESPONSE_HEADER_T * response_header = &smp_response->header;

   SCI_STATUS status = SCI_SUCCESS;

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_device),
      SCIF_LOG_OBJECT_REMOTE_DEVICE | SCIF_LOG_OBJECT_DOMAIN_DISCOVERY,
      "scif_sas_smp_remote_device_decode_discover_phy_control_response(0x%x, 0x%x) enter\n",
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
         "Phy Control function unaccepted result(0x%x)\n",
         response_header->function_result
      ));

      return SCI_FAILURE_RETRY_REQUIRED;
   }

   // continue the discover process.
   fw_device->protocol_device.smp_device.current_smp_request =
      SMP_FUNCTION_DISCOVER;

   // phy Control succeeded.
   return status;
}