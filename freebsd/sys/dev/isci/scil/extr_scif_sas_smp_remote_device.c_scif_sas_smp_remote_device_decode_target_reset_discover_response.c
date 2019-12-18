#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/ * domain; } ;
struct TYPE_11__ {scalar_t__ attached_device_type; } ;
struct TYPE_12__ {TYPE_1__ sas1_1; } ;
struct TYPE_16__ {int /*<<< orphan*/  attached_sas_address; TYPE_2__ u2; } ;
struct TYPE_15__ {scalar_t__ function_result; } ;
struct TYPE_13__ {TYPE_6__ discover; } ;
struct TYPE_14__ {TYPE_5__ header; TYPE_3__ response; } ;
typedef  TYPE_4__ SMP_RESPONSE_T ;
typedef  TYPE_5__ SMP_RESPONSE_HEADER_T ;
typedef  TYPE_6__ SMP_RESPONSE_DISCOVER_T ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_SAS_ADDRESS_T ;
typedef  TYPE_7__ SCIF_SAS_REMOTE_DEVICE_T ;
typedef  int /*<<< orphan*/  SCIF_SAS_DOMAIN_T ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  SCIF_LOG_ERROR (int /*<<< orphan*/ ) ; 
 int SCIF_LOG_OBJECT_DOMAIN_DISCOVERY ; 
 int SCIF_LOG_OBJECT_REMOTE_DEVICE ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCI_FAILURE_RETRY_REQUIRED ; 
 scalar_t__ SCI_INVALID_HANDLE ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 scalar_t__ SMP_NO_DEVICE_ATTACHED ; 
 scalar_t__ SMP_RESULT_FUNCTION_ACCEPTED ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_7__*) ; 
 scalar_t__ scif_domain_get_device_by_sas_address (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

SCI_STATUS scif_sas_smp_remote_device_decode_target_reset_discover_response(
   SCIF_SAS_REMOTE_DEVICE_T * fw_device,
   SMP_RESPONSE_T           * smp_response
)
{
   SCIF_SAS_DOMAIN_T  * fw_domain;
   SCI_SAS_ADDRESS_T attached_device_address;
   SMP_RESPONSE_DISCOVER_T * discover_response =
      &smp_response->response.discover;

   SMP_RESPONSE_HEADER_T * response_header = &smp_response->header;

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_device),
      SCIF_LOG_OBJECT_REMOTE_DEVICE | SCIF_LOG_OBJECT_DOMAIN_DISCOVERY,
      "scif_sas_smp_remote_device_decode_target_reset_discover_response(0x%x, 0x%x) enter\n",
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
         "Discover function result(0x%x)\n",
         response_header->function_result
      ));

      return SCI_FAILURE_RETRY_REQUIRED;
   }

   //only if there is device attached.
   if ( discover_response->u2.sas1_1.attached_device_type != SMP_NO_DEVICE_ATTACHED )
   {
      fw_domain = fw_device->domain;
      attached_device_address = discover_response->attached_sas_address;

      // the device should have already existed in the domian.
      ASSERT(scif_domain_get_device_by_sas_address(
                fw_domain,
                &attached_device_address
             ) != SCI_INVALID_HANDLE);
      return SCI_SUCCESS;
   }
   else
      return SCI_FAILURE_RETRY_REQUIRED;
}