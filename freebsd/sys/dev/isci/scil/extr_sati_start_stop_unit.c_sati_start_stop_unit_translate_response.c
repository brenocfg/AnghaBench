#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U8 ;
struct TYPE_6__ {int translated_command; } ;
struct TYPE_8__ {scalar_t__ state; TYPE_2__* device; TYPE_1__ command_specific_data; } ;
struct TYPE_7__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_3__ SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  SATI_STATUS ;

/* Variables and functions */
#define  ATA_FLUSH_CACHE 134 
#define  ATA_IDLE 133 
#define  ATA_IDLE_IMMED 132 
#define  ATA_MEDIA_EJECT 131 
#define  ATA_READ_VERIFY_SECTORS 130 
#define  ATA_STANDBY 129 
#define  ATA_STANDBY_IMMED 128 
 int ATA_STATUS_REG_ERROR_BIT ; 
 int /*<<< orphan*/  SATI_COMPLETE ; 
 int /*<<< orphan*/  SATI_DEVICE_STATE_IDLE ; 
 int /*<<< orphan*/  SATI_DEVICE_STATE_OPERATIONAL ; 
 int /*<<< orphan*/  SATI_DEVICE_STATE_STANDBY ; 
 int /*<<< orphan*/  SATI_DEVICE_STATE_STOPPED ; 
 int /*<<< orphan*/  SATI_FAILURE_CHECK_RESPONSE_DATA ; 
 int /*<<< orphan*/  SATI_SEQUENCE_INCOMPLETE ; 
 void* SATI_SEQUENCE_STATE_FINAL ; 
 scalar_t__ SATI_SEQUENCE_STATE_INCOMPLETE ; 
 int /*<<< orphan*/  SATI_START_STOP_UNIT_POWER_CONDITION (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCSI_ASCQ_INVALID_FIELD_IN_CDB ; 
 int /*<<< orphan*/  SCSI_ASCQ_NO_ADDITIONAL_SENSE ; 
 int /*<<< orphan*/  SCSI_ASC_COMMAND_SEQUENCE_ERROR ; 
 int /*<<< orphan*/  SCSI_ASC_INVALID_FIELD_IN_CDB ; 
 int /*<<< orphan*/  SCSI_ASC_MEDIA_LOAD_OR_EJECT_FAILED ; 
 int /*<<< orphan*/  SCSI_ASC_NO_ADDITIONAL_SENSE ; 
 int /*<<< orphan*/  SCSI_SENSE_ABORTED_COMMAND ; 
 int /*<<< orphan*/  SCSI_SENSE_ILLEGAL_REQUEST ; 
 int /*<<< orphan*/  SCSI_SENSE_NO_SENSE ; 
 int /*<<< orphan*/  SCSI_STATUS_CHECK_CONDITION ; 
 int /*<<< orphan*/  SCSI_STATUS_GOOD ; 
 int /*<<< orphan*/ * sati_cb_get_cdb_address (void*) ; 
 int /*<<< orphan*/ * sati_cb_get_d2h_register_fis_address (void*) ; 
 int sati_get_ata_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sati_scsi_sense_data_construct (TYPE_3__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

SATI_STATUS sati_start_stop_unit_translate_response(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   void                       * ata_io
)
{
   U8 * register_fis = sati_cb_get_d2h_register_fis_address(ata_io);
   U8 * cdb = sati_cb_get_cdb_address(scsi_io);

   if (sati_get_ata_status(register_fis) & ATA_STATUS_REG_ERROR_BIT)
   {
      switch ( sequence->command_specific_data.translated_command )
      {
         case ATA_FLUSH_CACHE:
         case ATA_STANDBY_IMMED:
         case ATA_IDLE_IMMED:
         case ATA_IDLE:
         case ATA_STANDBY:
            //Note: There is lack of reference in spec of the error handling for
            //READ_VERIFY command.
         case ATA_READ_VERIFY_SECTORS:
            sati_scsi_sense_data_construct(
               sequence,
               scsi_io,
               SCSI_STATUS_CHECK_CONDITION,
               SCSI_SENSE_ABORTED_COMMAND,
               SCSI_ASC_COMMAND_SEQUENCE_ERROR,
               SCSI_ASCQ_NO_ADDITIONAL_SENSE
            );
            break;

         case ATA_MEDIA_EJECT:
            sati_scsi_sense_data_construct(
               sequence,
               scsi_io,
               SCSI_STATUS_CHECK_CONDITION,
               SCSI_SENSE_ABORTED_COMMAND,
               SCSI_ASC_MEDIA_LOAD_OR_EJECT_FAILED,
               SCSI_ASCQ_NO_ADDITIONAL_SENSE
            );
            break;

         default:
            sati_scsi_sense_data_construct(
               sequence,
               scsi_io,
               SCSI_STATUS_CHECK_CONDITION,
               SCSI_SENSE_ILLEGAL_REQUEST,
               SCSI_ASC_INVALID_FIELD_IN_CDB,
               SCSI_ASCQ_INVALID_FIELD_IN_CDB
            );
            break;
      }
      sequence->state = SATI_SEQUENCE_STATE_FINAL;
      return SATI_FAILURE_CHECK_RESPONSE_DATA;
   }
   else
   {
      switch ( sequence->command_specific_data.translated_command )
      {
         case ATA_READ_VERIFY_SECTORS:

            sati_scsi_sense_data_construct(
               sequence,
               scsi_io,
               SCSI_STATUS_GOOD,
               SCSI_SENSE_NO_SENSE,
               SCSI_ASC_NO_ADDITIONAL_SENSE,
               SCSI_ASCQ_NO_ADDITIONAL_SENSE
            );
            //device state is now operational(active)
            sequence->device->state = SATI_DEVICE_STATE_OPERATIONAL;
            sequence->state = SATI_SEQUENCE_STATE_FINAL;
            break;

         case ATA_IDLE_IMMED:

            sati_scsi_sense_data_construct(
               sequence,
               scsi_io,
               SCSI_STATUS_GOOD,
               SCSI_SENSE_NO_SENSE,
               SCSI_ASC_NO_ADDITIONAL_SENSE,
               SCSI_ASCQ_NO_ADDITIONAL_SENSE
            );
            sequence->device->state = SATI_DEVICE_STATE_IDLE;
            sequence->state = SATI_SEQUENCE_STATE_FINAL;
            break;

         //These three commands will be issued when the power condition is 0x00 or 0x03
         case ATA_MEDIA_EJECT:
         case ATA_STANDBY:
         case ATA_STANDBY_IMMED:

            sati_scsi_sense_data_construct(
               sequence,
               scsi_io,
               SCSI_STATUS_GOOD,
               SCSI_SENSE_NO_SENSE,
               SCSI_ASC_NO_ADDITIONAL_SENSE,
               SCSI_ASCQ_NO_ADDITIONAL_SENSE
            );

            if( SATI_START_STOP_UNIT_POWER_CONDITION(cdb) == 0 )
            {
               sequence->device->state = SATI_DEVICE_STATE_STOPPED;
            }
            else
            {
               sequence->device->state = SATI_DEVICE_STATE_STANDBY;
            }
            sequence->state = SATI_SEQUENCE_STATE_FINAL;
            break;

         default:
            //FLUSH Cache command does not require any success handling
            break;
      }

      if (sequence->state == SATI_SEQUENCE_STATE_INCOMPLETE)
      {
         return SATI_SEQUENCE_INCOMPLETE;
      }
   }
   return SATI_COMPLETE;
}