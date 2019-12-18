#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  sequence; } ;
struct TYPE_9__ {TYPE_1__ stp; } ;
struct TYPE_10__ {TYPE_2__ parent; } ;
typedef  scalar_t__ SCI_STATUS ;
typedef  TYPE_3__ SCIF_SAS_TASK_REQUEST_T ;
typedef  int /*<<< orphan*/  SCIF_SAS_REQUEST_T ;
typedef  int /*<<< orphan*/  SCIF_SAS_REMOTE_DEVICE_T ;
typedef  int /*<<< orphan*/  SCIF_SAS_CONTROLLER_T ;
typedef  scalar_t__ SATI_STATUS ;

/* Variables and functions */
 scalar_t__ SATI_COMPLETE ; 
 scalar_t__ SATI_FAILURE_CHECK_RESPONSE_DATA ; 
 scalar_t__ SATI_SEQUENCE_INCOMPLETE ; 
 int /*<<< orphan*/  SCIF_LOG_OBJECT_TASK_MANAGEMENT ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ SCI_FAILURE ; 
 scalar_t__ SCI_FAILURE_IO_RESPONSE_VALID ; 
 scalar_t__ SCI_SAS_ABORT_TASK_SET ; 
 scalar_t__ SCI_SUCCESS ; 
 scalar_t__ sati_translate_task_response (int /*<<< orphan*/ *,TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scif_sas_stp_task_request_abort_task_set_failure_handler (int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ scif_sas_task_request_get_function (TYPE_3__*) ; 

__attribute__((used)) static
SCI_STATUS scif_sas_stp_core_cb_task_request_complete_handler(
   SCIF_SAS_CONTROLLER_T    * fw_controller,
   SCIF_SAS_REMOTE_DEVICE_T * fw_device,
   SCIF_SAS_REQUEST_T       * fw_request,
   SCI_STATUS               * completion_status
)
{
#if !defined(DISABLE_SATI_TASK_MANAGEMENT)
   SCIF_SAS_TASK_REQUEST_T * fw_task = (SCIF_SAS_TASK_REQUEST_T *) fw_request;

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_controller),
      SCIF_LOG_OBJECT_TASK_MANAGEMENT,
      "scif_sas_stp_core_cb_task_request_complete_handler(0x%x, 0x%x, 0x%x, 0x%x) enter\n",
      fw_controller, fw_device, fw_request, *completion_status
   ));

   // Translating the response is only necessary if some sort of error
   // occurred resulting in having the error bit set in the ATA status
   // register and values to decode in the ATA error register.
   if (  (*completion_status == SCI_SUCCESS)
      || (*completion_status == SCI_FAILURE_IO_RESPONSE_VALID) )
   {
      SATI_STATUS sati_status = sati_translate_task_response(
                                   &fw_task->parent.stp.sequence,
                                   fw_task,
                                   fw_task
                                );

      if (sati_status == SATI_COMPLETE)
         *completion_status = SCI_SUCCESS;
      else if (sati_status == SATI_FAILURE_CHECK_RESPONSE_DATA)
         *completion_status = SCI_FAILURE_IO_RESPONSE_VALID;
      else if (sati_status == SATI_SEQUENCE_INCOMPLETE)
      {
         // The translation indicates that additional SATA requests are
         // necessary to finish the original SCSI request.  As a result,
         // do not complete the IO and begin the next stage of the
         // translation.
         /// @todo multiple ATA commands are required, but not supported yet.
         return SCI_FAILURE;
      }
      else
      {
         // Something unexpected occurred during translation.  Fail the
         // IO request to the user.
         *completion_status = SCI_FAILURE;
      }
   }
   else  //A stp task request sometimes fails.
   {
      if (scif_sas_task_request_get_function(fw_task) == SCI_SAS_ABORT_TASK_SET)
      {
         scif_sas_stp_task_request_abort_task_set_failure_handler(
            fw_device, fw_task);
      }
   }

   return SCI_SUCCESS;
#else // !defined(DISABLE_SATI_TASK_MANAGEMENT)
   return SCI_FAILURE;
#endif // !defined(DISABLE_SATI_TASK_MANAGEMENT)
}