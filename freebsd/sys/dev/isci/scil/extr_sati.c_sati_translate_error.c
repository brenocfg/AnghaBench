#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int U8 ;
struct TYPE_4__ {scalar_t__ data_direction; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ SATI_TRANSLATOR_SEQUENCE_T ;

/* Variables and functions */
 int ATA_ERROR_REG_ICRC_BIT ; 
 int ATA_ERROR_REG_ID_NOT_FOUND_BIT ; 
 int ATA_ERROR_REG_MEDIA_CHANGE_BIT ; 
 int ATA_ERROR_REG_MEDIA_CHANGE_REQUEST_BIT ; 
 int ATA_ERROR_REG_NO_MEDIA_BIT ; 
 int ATA_ERROR_REG_UNCORRECTABLE_BIT ; 
 int ATA_ERROR_REG_WRITE_PROTECTED_BIT ; 
 scalar_t__ SATI_DATA_DIRECTION_OUT ; 
 int /*<<< orphan*/  SATI_SEQUENCE_STATE_READ_ERROR ; 
 int /*<<< orphan*/  SCSI_ASCQ_IU_CRC_ERROR_DETECTED ; 
 int /*<<< orphan*/  SCSI_ASCQ_LBA_OUT_OF_RANGE ; 
 int /*<<< orphan*/  SCSI_ASCQ_MEDIUM_NOT_PRESENT ; 
 int /*<<< orphan*/  SCSI_ASCQ_MEDIUM_REMOVAL_REQUEST ; 
 int /*<<< orphan*/  SCSI_ASCQ_NOT_READY_TO_READY_CHANGE ; 
 int /*<<< orphan*/  SCSI_ASCQ_NO_ADDITIONAL_SENSE ; 
 int /*<<< orphan*/  SCSI_ASCQ_UNRECOVERED_READ_ERROR ; 
 int /*<<< orphan*/  SCSI_ASCQ_WRITE_PROTECTED ; 
 int /*<<< orphan*/  SCSI_ASC_IU_CRC_ERROR_DETECTED ; 
 int /*<<< orphan*/  SCSI_ASC_LBA_OUT_OF_RANGE ; 
 int /*<<< orphan*/  SCSI_ASC_MEDIUM_NOT_PRESENT ; 
 int /*<<< orphan*/  SCSI_ASC_MEDIUM_REMOVAL_REQUEST ; 
 int /*<<< orphan*/  SCSI_ASC_NOT_READY_TO_READY_CHANGE ; 
 int /*<<< orphan*/  SCSI_ASC_NO_ADDITIONAL_SENSE ; 
 int /*<<< orphan*/  SCSI_ASC_UNRECOVERED_READ_ERROR ; 
 int /*<<< orphan*/  SCSI_ASC_WRITE_PROTECTED ; 
 int /*<<< orphan*/  SCSI_SENSE_ABORTED_COMMAND ; 
 int /*<<< orphan*/  SCSI_SENSE_DATA_PROTECT ; 
 int /*<<< orphan*/  SCSI_SENSE_ILLEGAL_REQUEST ; 
 int /*<<< orphan*/  SCSI_SENSE_MEDIUM_ERROR ; 
 int /*<<< orphan*/  SCSI_SENSE_NOT_READY ; 
 int /*<<< orphan*/  SCSI_SENSE_UNIT_ATTENTION ; 
 int /*<<< orphan*/  SCSI_STATUS_CHECK_CONDITION ; 
 int /*<<< orphan*/  sati_scsi_sense_data_construct (TYPE_1__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sati_translate_error(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   U8                           error
)
{
   if (error & ATA_ERROR_REG_NO_MEDIA_BIT)
   {
      sati_scsi_sense_data_construct(
         sequence,
         scsi_io,
         SCSI_STATUS_CHECK_CONDITION,
         SCSI_SENSE_NOT_READY,
         SCSI_ASC_MEDIUM_NOT_PRESENT,
         SCSI_ASCQ_MEDIUM_NOT_PRESENT
      );
   }
   else if (error & ATA_ERROR_REG_MEDIA_CHANGE_BIT)
   {
      sati_scsi_sense_data_construct(
         sequence,
         scsi_io,
         SCSI_STATUS_CHECK_CONDITION,
         SCSI_SENSE_UNIT_ATTENTION,
         SCSI_ASC_NOT_READY_TO_READY_CHANGE,
         SCSI_ASCQ_NOT_READY_TO_READY_CHANGE
      );
   }
   else if (error & ATA_ERROR_REG_MEDIA_CHANGE_REQUEST_BIT)
   {
      sati_scsi_sense_data_construct(
         sequence,
         scsi_io,
         SCSI_STATUS_CHECK_CONDITION,
         SCSI_SENSE_UNIT_ATTENTION,
         SCSI_ASC_MEDIUM_REMOVAL_REQUEST,
         SCSI_ASCQ_MEDIUM_REMOVAL_REQUEST
      );
   }
   else if (error & ATA_ERROR_REG_ID_NOT_FOUND_BIT)
   {
      sati_scsi_sense_data_construct(
         sequence,
         scsi_io,
         SCSI_STATUS_CHECK_CONDITION,
         SCSI_SENSE_ILLEGAL_REQUEST,
         SCSI_ASC_LBA_OUT_OF_RANGE,
         SCSI_ASCQ_LBA_OUT_OF_RANGE
      );
   }
   else if (error & ATA_ERROR_REG_UNCORRECTABLE_BIT)
   {
      //Mark the Sequence state as a read error so more sense data
      //can be returned later
      sequence->state = SATI_SEQUENCE_STATE_READ_ERROR;
      sati_scsi_sense_data_construct(
         sequence,
         scsi_io,
         SCSI_STATUS_CHECK_CONDITION,
         SCSI_SENSE_MEDIUM_ERROR,
         SCSI_ASC_UNRECOVERED_READ_ERROR,
         SCSI_ASCQ_UNRECOVERED_READ_ERROR
      );
   }
   else if (  (sequence->data_direction == SATI_DATA_DIRECTION_OUT)
           && (error & ATA_ERROR_REG_WRITE_PROTECTED_BIT) )
   {
      sati_scsi_sense_data_construct(
         sequence,
         scsi_io,
         SCSI_STATUS_CHECK_CONDITION,
         SCSI_SENSE_DATA_PROTECT,
         SCSI_ASC_WRITE_PROTECTED,
         SCSI_ASCQ_WRITE_PROTECTED
      );
   }
   else if (error & ATA_ERROR_REG_ICRC_BIT)
   {
      sati_scsi_sense_data_construct(
         sequence,
         scsi_io,
         SCSI_STATUS_CHECK_CONDITION,
         SCSI_SENSE_ABORTED_COMMAND,
         SCSI_ASC_IU_CRC_ERROR_DETECTED,
         SCSI_ASCQ_IU_CRC_ERROR_DETECTED
      );
   }
   else // (error & ATA_ERROR_REG_ABORT_BIT)
   {
      // The ABORT bit has the lowest precedence of all errors.
      // As a result, it is at the bottom of the conditional
      // statement.
      sati_scsi_sense_data_construct(
         sequence,
         scsi_io,
         SCSI_STATUS_CHECK_CONDITION,
         SCSI_SENSE_ABORTED_COMMAND,
         SCSI_ASC_NO_ADDITIONAL_SENSE,
         SCSI_ASCQ_NO_ADDITIONAL_SENSE
      );
   }
}