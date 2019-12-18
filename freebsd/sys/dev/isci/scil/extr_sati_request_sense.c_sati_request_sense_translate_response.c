#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U8 ;
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_5__ {int type; } ;
typedef  TYPE_1__ SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  SATI_STATUS ;

/* Variables and functions */
#define  ATA_ACTIVE_POWER_MODE 132 
 int /*<<< orphan*/  ATA_HIGH_REGISTER_THRESHOLD_EXCEEDED ; 
#define  ATA_IDLE_POWER_MODE 131 
 int /*<<< orphan*/  ATA_MID_REGISTER_THRESHOLD_EXCEEDED ; 
#define  ATA_STANDBY_POWER_MODE 130 
 int ATA_STATUS_REG_ERROR_BIT ; 
 int /*<<< orphan*/  SATI_COMPLETE ; 
 int /*<<< orphan*/  SATI_FAILURE ; 
 int /*<<< orphan*/  SATI_FAILURE_CHECK_RESPONSE_DATA ; 
#define  SATI_SEQUENCE_REQUEST_SENSE_CHECK_POWER_MODE 129 
#define  SATI_SEQUENCE_REQUEST_SENSE_SMART_RETURN_STATUS 128 
 int /*<<< orphan*/  SCSI_ASCQ_GENERAL_HARD_DRIVE_FAILURE ; 
 int /*<<< orphan*/  SCSI_ASCQ_NO_ADDITIONAL_SENSE ; 
 int /*<<< orphan*/  SCSI_ASCQ_POWER_STATE_CHANGE_TO_IDLE ; 
 int /*<<< orphan*/  SCSI_ASCQ_POWER_STATE_CHANGE_TO_STANDBY ; 
 int /*<<< orphan*/  SCSI_ASC_HARDWARE_IMPENDING_FAILURE ; 
 int /*<<< orphan*/  SCSI_ASC_NO_ADDITIONAL_SENSE ; 
 int /*<<< orphan*/  SCSI_ASC_POWER_STATE_CHANGE ; 
 int /*<<< orphan*/  SCSI_SENSE_ABORTED_COMMAND ; 
 int /*<<< orphan*/  SCSI_SENSE_NO_SENSE ; 
 int /*<<< orphan*/  SCSI_STATUS_CHECK_CONDITION ; 
 int /*<<< orphan*/ * sati_cb_get_d2h_register_fis_address (void*) ; 
 int /*<<< orphan*/  sati_get_ata_lba_high (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sati_get_ata_lba_mid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sati_get_ata_sector_count (int /*<<< orphan*/ *) ; 
 int sati_get_ata_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sati_request_sense_data_response_construct (TYPE_1__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_scsi_sense_data_construct (TYPE_1__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

SATI_STATUS sati_request_sense_translate_response(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   void                       * ata_io
)
{
   U8 * register_fis = sati_cb_get_d2h_register_fis_address(ata_io);
   U32 mid_register;
   U32 high_register;
   U32 sector_count;
   SATI_STATUS status = SATI_FAILURE;

   if(sati_get_ata_status(register_fis) & ATA_STATUS_REG_ERROR_BIT)
   {
      sati_scsi_sense_data_construct(
         sequence,
         scsi_io,
         SCSI_STATUS_CHECK_CONDITION,
         SCSI_SENSE_ABORTED_COMMAND,
         SCSI_ASC_NO_ADDITIONAL_SENSE ,
         SCSI_ASCQ_NO_ADDITIONAL_SENSE
      );
      status = SATI_FAILURE_CHECK_RESPONSE_DATA;
   }
   else
   {
      switch(sequence->type)
      {
         case SATI_SEQUENCE_REQUEST_SENSE_SMART_RETURN_STATUS:

            mid_register = sati_get_ata_lba_mid(register_fis);
            high_register = sati_get_ata_lba_high(register_fis);
            if(mid_register == ATA_MID_REGISTER_THRESHOLD_EXCEEDED
               && high_register == ATA_HIGH_REGISTER_THRESHOLD_EXCEEDED)
            {
               sati_request_sense_data_response_construct(
                  sequence,
                  scsi_io,
                  SCSI_SENSE_NO_SENSE,
                  SCSI_ASC_HARDWARE_IMPENDING_FAILURE,
                  SCSI_ASCQ_GENERAL_HARD_DRIVE_FAILURE
               );
               status = SATI_COMPLETE;
            }
            else
            {
               sati_request_sense_data_response_construct(
                  sequence,
                  scsi_io,
                  SCSI_SENSE_NO_SENSE,
                  SCSI_ASC_NO_ADDITIONAL_SENSE,
                  SCSI_ASCQ_NO_ADDITIONAL_SENSE
               );
               status = SATI_COMPLETE;
            }
         break;

         case SATI_SEQUENCE_REQUEST_SENSE_CHECK_POWER_MODE:

            sector_count = sati_get_ata_sector_count(register_fis);

            switch(sector_count)
            {
                case ATA_STANDBY_POWER_MODE:
                   sati_request_sense_data_response_construct(
                      sequence,
                      scsi_io,
                      SCSI_SENSE_NO_SENSE,
                      SCSI_ASC_POWER_STATE_CHANGE,
                      SCSI_ASCQ_POWER_STATE_CHANGE_TO_STANDBY
                   );
                   status = SATI_COMPLETE;
                break;

                case ATA_IDLE_POWER_MODE:
                   sati_request_sense_data_response_construct(
                      sequence,
                      scsi_io,
                      SCSI_SENSE_NO_SENSE,
                      SCSI_ASC_POWER_STATE_CHANGE,
                      SCSI_ASCQ_POWER_STATE_CHANGE_TO_IDLE
                   );
                   status = SATI_COMPLETE;
                break;

                case ATA_ACTIVE_POWER_MODE:
                   sati_request_sense_data_response_construct(
                      sequence,
                      scsi_io,
                      SCSI_SENSE_NO_SENSE,
                      SCSI_ASC_NO_ADDITIONAL_SENSE,
                      SCSI_ASCQ_NO_ADDITIONAL_SENSE
                   );
                   status = SATI_COMPLETE;
                break;

                default:
                break;
             }
         break;

         default:
            sati_request_sense_data_response_construct(
               sequence,
               scsi_io,
               SCSI_SENSE_NO_SENSE,
               SCSI_ASC_NO_ADDITIONAL_SENSE,
               SCSI_ASCQ_NO_ADDITIONAL_SENSE
            );
            status = SATI_COMPLETE;
      }
   }

   return status;
}