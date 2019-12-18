#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int U8 ;
struct TYPE_7__ {int ncq_tag; scalar_t__ nq; int /*<<< orphan*/  error; } ;
struct TYPE_6__ {scalar_t__ state; } ;
typedef  int /*<<< orphan*/  SCI_IO_STATUS ;
typedef  TYPE_1__ SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  SATI_STATUS ;
typedef  TYPE_2__ ATA_NCQ_COMMAND_ERROR_LOG_T ;

/* Variables and functions */
 int /*<<< orphan*/  SATI_COMPLETE ; 
 scalar_t__ SATI_SEQUENCE_STATE_FINAL ; 
 scalar_t__ SATI_SEQUENCE_STATE_READ_ERROR ; 
 scalar_t__ SATI_SEQUENCE_STATE_TRANSLATE_DATA ; 
 int /*<<< orphan*/  SCI_IO_FAILURE_RESPONSE_VALID ; 
 int /*<<< orphan*/  SCI_IO_FAILURE_TERMINATED ; 
 int /*<<< orphan*/  SCSI_ASCQ_UNRECOVERED_READ_ERROR ; 
 int /*<<< orphan*/  SCSI_ASC_UNRECOVERED_READ_ERROR ; 
 int /*<<< orphan*/  SCSI_SENSE_MEDIUM_ERROR ; 
 int /*<<< orphan*/  SCSI_STATUS_CHECK_CONDITION ; 
 int /*<<< orphan*/  sati_cb_device_get_request_by_ncq_tag (void*,int,void*) ; 
 int /*<<< orphan*/  sati_cb_io_request_complete (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_scsi_read_ncq_error_sense_construct (TYPE_1__*,void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_translate_error (TYPE_1__*,void*,int /*<<< orphan*/ ) ; 

SATI_STATUS sati_abort_task_set_translate_data(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * ata_input_data,
   void                       * scsi_task
)
{
   ATA_NCQ_COMMAND_ERROR_LOG_T * log =
      (ATA_NCQ_COMMAND_ERROR_LOG_T *)ata_input_data;
   U8 tag_index;

   sequence->state = SATI_SEQUENCE_STATE_TRANSLATE_DATA;

   for (tag_index = 0; tag_index < 32; tag_index++)
   {
      void *        matching_command;
      SCI_IO_STATUS completion_status;
      sati_cb_device_get_request_by_ncq_tag(
         scsi_task,
         tag_index,
         matching_command
      );

      if (matching_command != NULL)
      {
         if (
              (log->ncq_tag == tag_index) &&
              (log->nq == 0) // nq==1 means a non-queued command
                             //  caused this failure
            )
         {
            sati_translate_error(sequence, matching_command, log->error);
            completion_status = SCI_IO_FAILURE_RESPONSE_VALID;

            if(sequence->state == SATI_SEQUENCE_STATE_READ_ERROR)
            {
               //Uncorrectable read error, return additional sense data
               sati_scsi_read_ncq_error_sense_construct(
                  sequence,
                  matching_command,
                  ata_input_data,
                  SCSI_STATUS_CHECK_CONDITION,
                  SCSI_SENSE_MEDIUM_ERROR,
                  SCSI_ASC_UNRECOVERED_READ_ERROR,
                  SCSI_ASCQ_UNRECOVERED_READ_ERROR
               );
            }
         }
         else
         {
            completion_status = SCI_IO_FAILURE_TERMINATED;
         }

         sati_cb_io_request_complete(matching_command, completion_status);
      }
   }

   sequence->state = SATI_SEQUENCE_STATE_FINAL;

   return SATI_COMPLETE;
}