#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ U8 ;
struct TYPE_15__ {scalar_t__ retry_count; } ;
struct TYPE_12__ {int current_smp_request; int /*<<< orphan*/  current_activity_phy_index; scalar_t__ io_retry_count; } ;
struct TYPE_13__ {TYPE_2__ smp_device; } ;
struct TYPE_14__ {TYPE_3__ protocol_device; TYPE_1__* domain; } ;
struct TYPE_11__ {int /*<<< orphan*/ * controller; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  TYPE_4__ SCIF_SAS_REMOTE_DEVICE_T ;
typedef  TYPE_5__ SCIF_SAS_IO_REQUEST_T ;
typedef  int /*<<< orphan*/  SCIF_SAS_CONTROLLER_T ;

/* Variables and functions */
 int SCIF_LOG_OBJECT_DOMAIN_DISCOVERY ; 
 int SCIF_LOG_OBJECT_IO_REQUEST ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCI_FAILURE_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
#define  SMP_FUNCTION_DISCOVER 130 
#define  SMP_FUNCTION_REPORT_GENERAL 129 
#define  SMP_FUNCTION_REPORT_PHY_SATA 128 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_4__*) ; 
 int /*<<< orphan*/  scif_cb_start_internal_io_task_schedule (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scif_sas_controller_start_high_priority_io ; 
 void* scif_sas_smp_request_construct_discover (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* scif_sas_smp_request_construct_report_general (int /*<<< orphan*/ *,TYPE_4__*) ; 
 void* scif_sas_smp_request_construct_report_phy_sata (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 

SCI_STATUS scif_sas_smp_internal_request_retry(
   SCIF_SAS_REMOTE_DEVICE_T * fw_device
)
{
   SCIF_SAS_CONTROLLER_T * fw_controller;
   SCIF_SAS_IO_REQUEST_T * new_io;
   void                  * new_request_memory = NULL;
   U8 retry_count = fw_device->protocol_device.smp_device.io_retry_count;

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_device),
      SCIF_LOG_OBJECT_IO_REQUEST | SCIF_LOG_OBJECT_DOMAIN_DISCOVERY,
      "scif_sas_smp_internal_request_retry(0x%x, 0x%x) time %d!\n",
      fw_device, retry_count
   ));

   fw_controller = fw_device->domain->controller;

   switch (fw_device->protocol_device.smp_device.current_smp_request)
   {
      case SMP_FUNCTION_REPORT_GENERAL:
         new_request_memory = scif_sas_smp_request_construct_report_general(
            fw_controller, fw_device
         );
         break;

      case SMP_FUNCTION_DISCOVER:
         //We are retrying an internal io. So we are going to allocate
         //a new memory from internal io memory pool.
         new_request_memory = scif_sas_smp_request_construct_discover(
            fw_controller, fw_device,
            fw_device->protocol_device.smp_device.current_activity_phy_index,
            NULL, NULL
         );

         break;

      case SMP_FUNCTION_REPORT_PHY_SATA:
         new_request_memory = scif_sas_smp_request_construct_report_phy_sata(
            fw_controller, fw_device,
            fw_device->protocol_device.smp_device.current_activity_phy_index
         );
         break;

      default:
         //unsupported case, TBD
         break;
   } //end of switch

   if (new_request_memory != NULL)
   {
      //set the retry count to new built smp request.
      new_io = (SCIF_SAS_IO_REQUEST_T *) new_request_memory;
      new_io->retry_count = ++retry_count;

      //need to schedule the DPC here.
      scif_cb_start_internal_io_task_schedule(
            fw_controller,
            scif_sas_controller_start_high_priority_io,
            fw_controller
         );

      return SCI_SUCCESS;
   }
   else
      return SCI_FAILURE_INSUFFICIENT_RESOURCES;

}