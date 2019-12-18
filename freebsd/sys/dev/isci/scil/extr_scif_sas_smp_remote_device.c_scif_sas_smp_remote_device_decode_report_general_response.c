#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ U8 ;
struct TYPE_16__ {scalar_t__ element_count; } ;
struct TYPE_17__ {int expander_route_indexes; TYPE_3__ smp_phy_list; void* is_able_to_config_others; void* is_externally_configurable; void* is_table_to_table_supported; scalar_t__ number_of_phys; } ;
struct TYPE_18__ {TYPE_4__ smp_device; } ;
struct TYPE_22__ {TYPE_5__ protocol_device; TYPE_2__* domain; int /*<<< orphan*/ * containing_device; } ;
struct TYPE_21__ {scalar_t__ function_result; } ;
struct TYPE_20__ {int expander_route_indexes; scalar_t__ configuring; scalar_t__ configures_others; scalar_t__ configurable_route_table; scalar_t__ table_to_table_supported; scalar_t__ number_of_phys; } ;
struct TYPE_14__ {TYPE_7__ report_general; } ;
struct TYPE_19__ {TYPE_8__ header; TYPE_1__ response; } ;
struct TYPE_15__ {int /*<<< orphan*/  is_config_route_table_needed; } ;
typedef  TYPE_6__ SMP_RESPONSE_T ;
typedef  TYPE_7__ SMP_RESPONSE_REPORT_GENERAL_T ;
typedef  TYPE_8__ SMP_RESPONSE_HEADER_T ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  TYPE_9__ SCIF_SAS_REMOTE_DEVICE_T ;
typedef  void* BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_LOG_ERROR (int /*<<< orphan*/ ) ; 
 int SCIF_LOG_OBJECT_DOMAIN_DISCOVERY ; 
 int SCIF_LOG_OBJECT_REMOTE_DEVICE ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCI_FAILURE ; 
 int /*<<< orphan*/  SCI_FAILURE_RETRY_REQUIRED ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 scalar_t__ SMP_RESULT_FUNCTION_ACCEPTED ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_9__*) ; 
 int /*<<< orphan*/  scif_sas_smp_remote_device_populate_smp_phy_list (TYPE_9__*) ; 

SCI_STATUS scif_sas_smp_remote_device_decode_report_general_response(
   SCIF_SAS_REMOTE_DEVICE_T * fw_device,
   SMP_RESPONSE_T           * smp_response
)
{
   SMP_RESPONSE_REPORT_GENERAL_T * report_general_response =
      &smp_response->response.report_general;

   SMP_RESPONSE_HEADER_T * response_header = &smp_response->header;

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_device),
      SCIF_LOG_OBJECT_REMOTE_DEVICE | SCIF_LOG_OBJECT_DOMAIN_DISCOVERY,
      "scif_sas_smp_remote_device_decode_report_general_response(0x%x, 0x%x) enter\n",
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
         "Report General function result(0x%x)\n",
         response_header->function_result
      ));

      return SCI_FAILURE;
   }

   //get info from report general response.
   fw_device->protocol_device.smp_device.number_of_phys =
      (U8)report_general_response->number_of_phys;

   //currently there is byte swap issue in U16 data.
   fw_device->protocol_device.smp_device.expander_route_indexes =
      ((report_general_response->expander_route_indexes & 0xff) << 8) |
      ((report_general_response->expander_route_indexes & 0xff00) >> 8);

   fw_device->protocol_device.smp_device.is_table_to_table_supported =
      (BOOL)report_general_response->table_to_table_supported;

   fw_device->protocol_device.smp_device.is_externally_configurable =
      (BOOL)report_general_response->configurable_route_table;

   fw_device->protocol_device.smp_device.is_able_to_config_others =
      (BOOL)report_general_response->configures_others;

   //If the top level expander of a domain is able to configure others,
   //no config route table is needed in the domain. Or else,
   //we'll let all the externally configurable expanders in the damain
   //configure route table.
   if (fw_device->containing_device == NULL
       && ! fw_device->protocol_device.smp_device.is_able_to_config_others)
      fw_device->domain->is_config_route_table_needed = TRUE;

   //knowing number of phys this expander has, we can allocate all the smp phys for
   //this expander now if it is not done already.
   if (fw_device->protocol_device.smp_device.smp_phy_list.element_count == 0)
      scif_sas_smp_remote_device_populate_smp_phy_list(fw_device);

   if (report_general_response->configuring)
      return SCI_FAILURE_RETRY_REQUIRED;

   return SCI_SUCCESS;
}