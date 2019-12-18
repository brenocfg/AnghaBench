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
struct TYPE_12__ {int /*<<< orphan*/  sati_device; } ;
struct TYPE_13__ {TYPE_2__ stp_device; } ;
struct TYPE_16__ {TYPE_3__ protocol_device; } ;
struct TYPE_11__ {int /*<<< orphan*/  sequence; } ;
struct TYPE_14__ {int /*<<< orphan*/  protocol_complete_handler; int /*<<< orphan*/  core_object; TYPE_1__ stp; TYPE_6__* device; } ;
struct TYPE_15__ {TYPE_4__ parent; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  TYPE_5__ SCIF_SAS_TASK_REQUEST_T ;
typedef  TYPE_6__ SCIF_SAS_REMOTE_DEVICE_T ;
typedef  scalar_t__ SATI_STATUS ;

/* Variables and functions */
 scalar_t__ SATI_SUCCESS ; 
 int /*<<< orphan*/  SCIF_LOG_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIF_LOG_OBJECT_TASK_MANAGEMENT ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCI_FAILURE ; 
 scalar_t__ sati_translate_task_management (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_5__*,TYPE_5__*) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_5__*) ; 
 int /*<<< orphan*/  scic_task_request_construct_sata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_sas_stp_core_cb_task_request_complete_handler ; 

SCI_STATUS scif_sas_stp_task_request_construct(
   SCIF_SAS_TASK_REQUEST_T * fw_task
)
{
   SCI_STATUS                 sci_status = SCI_FAILURE;

#if !defined(DISABLE_SATI_TASK_MANAGEMENT)
   SATI_STATUS                sati_status;
   SCIF_SAS_REMOTE_DEVICE_T * fw_device  = fw_task->parent.device;

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_task),
      SCIF_LOG_OBJECT_TASK_MANAGEMENT,
      "scif_sas_stp_task_request_construct(0x%x) enter\n",
      fw_task
   ));

   // The translator will indirectly invoke core methods to set the fields
   // of the ATA register FIS inside of this method.
   sati_status = sati_translate_task_management(
                    &fw_task->parent.stp.sequence,
                    &fw_device->protocol_device.stp_device.sati_device,
                    fw_task,
                    fw_task
                 );

   if (sati_status == SATI_SUCCESS)
   {
      sci_status = scic_task_request_construct_sata(fw_task->parent.core_object);
      //fw_task->parent.state_handlers = &stp_io_request_constructed_handlers;
      fw_task->parent.protocol_complete_handler =
         scif_sas_stp_core_cb_task_request_complete_handler;
   }
   else
   {
      SCIF_LOG_ERROR((
         sci_base_object_get_logger(fw_task),
         SCIF_LOG_OBJECT_TASK_MANAGEMENT,
         "Task 0x%x received unexpected SAT translation failure 0x%x\n",
         fw_task, sati_status
      ));
   }
#endif // !defined(DISABLE_SATI_TASK_MANAGEMENT)

   return sci_status;
}