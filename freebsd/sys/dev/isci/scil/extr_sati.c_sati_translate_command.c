#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_43__   TYPE_3__ ;
typedef  struct TYPE_42__   TYPE_2__ ;
typedef  struct TYPE_41__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U8 ;
struct TYPE_43__ {scalar_t__ state; } ;
struct TYPE_41__ {scalar_t__ scratch; } ;
struct TYPE_42__ {scalar_t__ state; void* is_sense_response_set; scalar_t__ number_data_bytes_set; TYPE_1__ command_specific_data; TYPE_3__* device; void* is_translate_response_required; } ;
typedef  TYPE_2__ SATI_TRANSLATOR_SEQUENCE_T ;
typedef  scalar_t__ SATI_STATUS ;
typedef  TYPE_3__ SATI_DEVICE_T ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  SATA_FIS_TYPE_REGH2D ; 
 scalar_t__ SATI_DEVICE_STATE_DEVICE_FAULT_OCCURRED ; 
 scalar_t__ SATI_FAILURE ; 
 scalar_t__ SATI_FAILURE_CHECK_RESPONSE_DATA ; 
 scalar_t__ SATI_SEQUENCE_STATE_INITIAL ; 
 int /*<<< orphan*/  SCSI_ASCQ_INTERNAL_TARGET_FAILURE ; 
 int /*<<< orphan*/  SCSI_ASCQ_INVALID_COMMAND_OPERATION_CODE ; 
 int /*<<< orphan*/  SCSI_ASCQ_INVALID_FIELD_IN_CDB ; 
 int /*<<< orphan*/  SCSI_ASC_INTERNAL_TARGET_FAILURE ; 
 int /*<<< orphan*/  SCSI_ASC_INVALID_COMMAND_OPERATION_CODE ; 
 int /*<<< orphan*/  SCSI_ASC_INVALID_FIELD_IN_CDB ; 
 int /*<<< orphan*/  SCSI_ASC_LOGICAL_UNIT_NOT_SUPPORTED ; 
#define  SCSI_ATA_PASSTHRU_12 165 
#define  SCSI_ATA_PASSTHRU_16 164 
 int SCSI_CONTROL_BYTE_NACA_BIT_ENABLE ; 
#define  SCSI_INQUIRY 163 
#define  SCSI_LOG_SENSE 162 
#define  SCSI_MODE_SELECT_10 161 
#define  SCSI_MODE_SELECT_6 160 
#define  SCSI_MODE_SENSE_10 159 
#define  SCSI_MODE_SENSE_6 158 
#define  SCSI_PERSISTENT_RESERVE_IN 157 
#define  SCSI_PERSISTENT_RESERVE_OUT 156 
#define  SCSI_READ_10 155 
#define  SCSI_READ_12 154 
#define  SCSI_READ_16 153 
#define  SCSI_READ_6 152 
#define  SCSI_READ_BUFFER 151 
#define  SCSI_READ_CAPACITY_10 150 
#define  SCSI_REASSIGN_BLOCKS 149 
#define  SCSI_REPORT_LUNS 148 
#define  SCSI_REQUEST_SENSE 147 
 int /*<<< orphan*/  SCSI_SENSE_HARDWARE_ERROR ; 
 int /*<<< orphan*/  SCSI_SENSE_ILLEGAL_REQUEST ; 
#define  SCSI_SERVICE_ACTION_IN_16 146 
 int SCSI_SERVICE_ACTION_IN_CODES_READ_CAPACITY_16 ; 
 int SCSI_SERVICE_ACTION_MASK ; 
#define  SCSI_START_STOP_UNIT 145 
 int /*<<< orphan*/  SCSI_STATUS_CHECK_CONDITION ; 
#define  SCSI_SYNCHRONIZE_CACHE_10 144 
#define  SCSI_SYNCHRONIZE_CACHE_16 143 
#define  SCSI_TEST_UNIT_READY 142 
#define  SCSI_UNMAP 141 
#define  SCSI_VERIFY_10 140 
#define  SCSI_VERIFY_12 139 
#define  SCSI_VERIFY_16 138 
#define  SCSI_WRITE_10 137 
#define  SCSI_WRITE_12 136 
#define  SCSI_WRITE_16 135 
#define  SCSI_WRITE_6 134 
#define  SCSI_WRITE_AND_VERIFY_10 133 
#define  SCSI_WRITE_AND_VERIFY_12 132 
#define  SCSI_WRITE_AND_VERIFY_16 131 
#define  SCSI_WRITE_BUFFER 130 
#define  SCSI_WRITE_LONG_10 129 
#define  SCSI_WRITE_LONG_16 128 
 int /*<<< orphan*/ * sati_cb_get_cdb_address (void*) ; 
 int sati_cb_get_cdb_length (void*) ; 
 int /*<<< orphan*/ * sati_cb_get_h2d_register_fis_address (void*) ; 
 scalar_t__ sati_cb_get_lun (void*) ; 
 int sati_get_cdb_byte (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sati_inquiry_translate_command (TYPE_2__*,void*,void*) ; 
 scalar_t__ sati_log_sense_translate_command (TYPE_2__*,void*,void*) ; 
 scalar_t__ sati_mode_select_10_translate_command (TYPE_2__*,void*,void*) ; 
 scalar_t__ sati_mode_select_6_translate_command (TYPE_2__*,void*,void*) ; 
 scalar_t__ sati_mode_sense_10_translate_command (TYPE_2__*,void*,void*) ; 
 scalar_t__ sati_mode_sense_6_translate_command (TYPE_2__*,void*,void*) ; 
 scalar_t__ sati_passthrough_12_translate_command (TYPE_2__*,void*,void*) ; 
 scalar_t__ sati_passthrough_16_translate_command (TYPE_2__*,void*,void*) ; 
 scalar_t__ sati_read_10_translate_command (TYPE_2__*,void*,void*) ; 
 scalar_t__ sati_read_12_translate_command (TYPE_2__*,void*,void*) ; 
 scalar_t__ sati_read_16_translate_command (TYPE_2__*,void*,void*) ; 
 scalar_t__ sati_read_6_translate_command (TYPE_2__*,void*,void*) ; 
 scalar_t__ sati_read_buffer_translate_command (TYPE_2__*,void*,void*) ; 
 scalar_t__ sati_read_capacity_10_translate_command (TYPE_2__*,void*,void*) ; 
 scalar_t__ sati_read_capacity_16_translate_command (TYPE_2__*,void*,void*) ; 
 scalar_t__ sati_reassign_blocks_translate_command (TYPE_2__*,void*,void*) ; 
 scalar_t__ sati_report_luns_translate_command (TYPE_2__*,void*,void*) ; 
 scalar_t__ sati_request_sense_translate_command (TYPE_2__*,void*,void*) ; 
 int /*<<< orphan*/  sati_scsi_sense_data_construct (TYPE_2__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_set_sata_command_flag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sati_set_sata_fis_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sati_start_stop_unit_translate_command (TYPE_2__*,void*,void*) ; 
 scalar_t__ sati_synchronize_cache_translate_command (TYPE_2__*,void*,void*) ; 
 scalar_t__ sati_test_unit_ready_translate_command (TYPE_2__*,void*,void*) ; 
 scalar_t__ sati_unmap_translate_command (TYPE_2__*,void*,void*) ; 
 scalar_t__ sati_verify_10_translate_command (TYPE_2__*,void*,void*) ; 
 scalar_t__ sati_verify_12_translate_command (TYPE_2__*,void*,void*) ; 
 scalar_t__ sati_verify_16_translate_command (TYPE_2__*,void*,void*) ; 
 scalar_t__ sati_write_10_translate_command (TYPE_2__*,void*,void*) ; 
 scalar_t__ sati_write_12_translate_command (TYPE_2__*,void*,void*) ; 
 scalar_t__ sati_write_16_translate_command (TYPE_2__*,void*,void*) ; 
 scalar_t__ sati_write_6_translate_command (TYPE_2__*,void*,void*) ; 
 scalar_t__ sati_write_and_verify_10_translate_command (TYPE_2__*,void*,void*) ; 
 scalar_t__ sati_write_and_verify_12_translate_command (TYPE_2__*,void*,void*) ; 
 scalar_t__ sati_write_and_verify_16_translate_command (TYPE_2__*,void*,void*) ; 
 scalar_t__ sati_write_buffer_translate_command (TYPE_2__*,void*,void*) ; 
 scalar_t__ sati_write_long_translate_command (TYPE_2__*,void*,void*) ; 

SATI_STATUS sati_translate_command(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   SATI_DEVICE_T              * sati_device,
   void                       * scsi_io,
   void                       * ata_io
)
{
   SATI_STATUS   status = SATI_FAILURE;
   U8          * cdb = sati_cb_get_cdb_address(scsi_io);

   //No sense response has been set for the translation sequence yet
   sequence->is_sense_response_set          = FALSE;
   // Default to no translation response required
   sequence->is_translate_response_required = FALSE;
   // Assign sati_device to sequence
   sequence->device  = sati_device;

   /**
    * Fail any I/O request with LUN != 0
    */
   if (sati_cb_get_lun(scsi_io) != 0)
   {
      sati_scsi_sense_data_construct(
         sequence,
         scsi_io,
         SCSI_STATUS_CHECK_CONDITION,
         SCSI_SENSE_ILLEGAL_REQUEST,
         SCSI_ASC_LOGICAL_UNIT_NOT_SUPPORTED,
         0
      );
      return SATI_FAILURE_CHECK_RESPONSE_DATA;
   }

   /**
    * SAT dictates:
    * - the NACA bit in the control byte (last byte) must be 0
    */
   if ( (sati_get_cdb_byte(cdb, sati_cb_get_cdb_length(scsi_io) - 1)
         & SCSI_CONTROL_BYTE_NACA_BIT_ENABLE))
   {
      sati_scsi_sense_data_construct(
         sequence,
         scsi_io,
         SCSI_STATUS_CHECK_CONDITION,
         SCSI_SENSE_ILLEGAL_REQUEST,
         SCSI_ASC_INVALID_FIELD_IN_CDB,
         SCSI_ASCQ_INVALID_FIELD_IN_CDB
      );
      return SATI_FAILURE_CHECK_RESPONSE_DATA;
   }

   /**
    * Per SAT "Error and sense reporting" section.  All subsequent IOs after
    * a device fault should receive INTERNAL TARGET FAILURE sense data.
    */
   if (sati_device->state == SATI_DEVICE_STATE_DEVICE_FAULT_OCCURRED)
   {
      sati_scsi_sense_data_construct(
         sequence,
         scsi_io,
         SCSI_STATUS_CHECK_CONDITION,
         SCSI_SENSE_HARDWARE_ERROR,
         SCSI_ASC_INTERNAL_TARGET_FAILURE,
         SCSI_ASCQ_INTERNAL_TARGET_FAILURE
      );
      return SATI_FAILURE_CHECK_RESPONSE_DATA;
   }

   if(sequence->state == SATI_SEQUENCE_STATE_INITIAL)
   {
      sequence->command_specific_data.scratch = 0;
      sequence->number_data_bytes_set = 0;
   }


#ifdef SATI_TRANSPORT_SUPPORTS_SATA
   {
      U8 * register_fis = sati_cb_get_h2d_register_fis_address(ata_io);
      sati_set_sata_command_flag(register_fis);
      sati_set_sata_fis_type(register_fis, SATA_FIS_TYPE_REGH2D);
   }
#endif // SATI_TRANSPORT_SUPPORTS_SATA

   // Look at the first byte to determine the SCSI command to translate.
   switch (sati_get_cdb_byte(cdb, 0))
   {
#if !defined(DISABLE_SATI_REPORT_LUNS)
      case SCSI_REPORT_LUNS:
         status = sati_report_luns_translate_command(
                     sequence, scsi_io, ata_io
                  );
      break;
#endif // !defined(DISABLE_SATI_REPORT_LUNS)

#if !defined(DISABLE_SATI_INQUIRY)
      case SCSI_INQUIRY:
         status = sati_inquiry_translate_command(
                     sequence, scsi_io, ata_io
                  );
      break;
#endif // !defined(DISABLE_SATI_INQUIRY)

#if !defined(DISABLE_SATI_MODE_SENSE)
      case SCSI_MODE_SENSE_6:
         status = sati_mode_sense_6_translate_command(
                     sequence, scsi_io, ata_io
                  );
      break;

      case SCSI_MODE_SENSE_10:
         status = sati_mode_sense_10_translate_command(
                     sequence, scsi_io, ata_io
                  );
      break;
#endif // !defined(DISABLE_SATI_MODE_SENSE)

#if !defined(DISABLE_SATI_MODE_SELECT)
      case SCSI_MODE_SELECT_6:
         status = sati_mode_select_6_translate_command(
                     sequence, scsi_io, ata_io
                  );
      break;

      case SCSI_MODE_SELECT_10:
         status = sati_mode_select_10_translate_command(
                     sequence, scsi_io, ata_io
                  );
      break;
#endif // !defined(DISABLE_SATI_MODE_SELECT)

#if !defined(DISABLE_SATI_TEST_UNIT_READY)
      case SCSI_TEST_UNIT_READY:
         status = sati_test_unit_ready_translate_command(
                     sequence, scsi_io, ata_io
                  );
      break;
#endif // !defined(DISABLE_SATI_TEST_UNIT_READY)

#if !defined(DISABLE_SATI_READ_CAPACITY)
      case SCSI_READ_CAPACITY_10:
         status = sati_read_capacity_10_translate_command(
                     sequence, scsi_io, ata_io
                  );
      break;

      case SCSI_SERVICE_ACTION_IN_16:
         if ( (sati_get_cdb_byte(cdb, 1) & SCSI_SERVICE_ACTION_MASK)
              == SCSI_SERVICE_ACTION_IN_CODES_READ_CAPACITY_16)
            status = sati_read_capacity_16_translate_command(
                        sequence, scsi_io, ata_io
                     );
         else
            status = SATI_FAILURE_CHECK_RESPONSE_DATA;
      break;
#endif // !defined(DISABLE_SATI_READ_CAPACITY)

#if !defined(DISABLE_SATI_REQUEST_SENSE)
      case SCSI_REQUEST_SENSE:
         status = sati_request_sense_translate_command(
                     sequence, scsi_io, ata_io
                  );
      break;
#endif // !defined(DISABLE_SATI_REQUEST_SENSE)

      case SCSI_READ_6:
         status = sati_read_6_translate_command(sequence, scsi_io, ata_io);
      break;

      case SCSI_READ_10:
         status = sati_read_10_translate_command(sequence, scsi_io, ata_io);
      break;

      case SCSI_READ_12:
         status = sati_read_12_translate_command(sequence, scsi_io, ata_io);
      break;

      case SCSI_READ_16:
         status = sati_read_16_translate_command(sequence, scsi_io, ata_io);
      break;

      case SCSI_WRITE_6:
         status = sati_write_6_translate_command(sequence, scsi_io, ata_io);
      break;

      case SCSI_WRITE_10:
         status = sati_write_10_translate_command(sequence, scsi_io, ata_io);
      break;

      case SCSI_WRITE_12:
         status = sati_write_12_translate_command(sequence, scsi_io, ata_io);
      break;

      case SCSI_WRITE_16:
         status = sati_write_16_translate_command(sequence, scsi_io, ata_io);
      break;

#if !defined(DISABLE_SATI_VERIFY)
      case SCSI_VERIFY_10:
         status = sati_verify_10_translate_command(sequence, scsi_io, ata_io);
      break;

      case SCSI_VERIFY_12:
         status = sati_verify_12_translate_command(sequence, scsi_io, ata_io);
      break;

      case SCSI_VERIFY_16:
         status = sati_verify_16_translate_command(sequence, scsi_io, ata_io);
      break;
#endif // !defined(DISABLE_SATI_VERIFY)

#if    !defined(DISABLE_SATI_WRITE_AND_VERIFY)  \
   && !defined(DISABLE_SATI_VERIFY)        \
   && !defined(DISABLE_SATI_WRITE)

      case SCSI_WRITE_AND_VERIFY_10:
         status = sati_write_and_verify_10_translate_command(sequence, scsi_io, ata_io);
      break;

      case SCSI_WRITE_AND_VERIFY_12:
         status = sati_write_and_verify_12_translate_command(sequence, scsi_io, ata_io);
      break;

      case SCSI_WRITE_AND_VERIFY_16:
         status = sati_write_and_verify_16_translate_command(sequence, scsi_io, ata_io);
      break;
#endif //    !defined(DISABLE_SATI_WRITE_AND_VERIFY)
      // && !defined(DISABLE_SATI_VERIFY)
      // && !defined(DISABLE_SATI_WRITE)

#if !defined(DISABLE_SATI_REASSIGN_BLOCKS)
      case SCSI_REASSIGN_BLOCKS:
         status = sati_reassign_blocks_translate_command(sequence, scsi_io, ata_io);
      break;
#endif // !defined(DISABLE_SATI_REASSIGN_BLOCKS)

#if !defined(DISABLE_SATI_SYNCHRONIZE_CACHE)
      case SCSI_SYNCHRONIZE_CACHE_10:
      case SCSI_SYNCHRONIZE_CACHE_16:
         status = sati_synchronize_cache_translate_command(sequence, scsi_io, ata_io);
      break;
#endif // !defined(DISABLE_SATI_SYNCHRONIZE_CACHE)

#if !defined(DISABLE_SATI_START_STOP_UNIT)
      case SCSI_START_STOP_UNIT:
         status = sati_start_stop_unit_translate_command(
                     sequence, scsi_io, ata_io
                  );
      break;
#endif // !defined(DISABLE_SATI_START_STOP_UNIT)

#if !defined(DISABLE_SATI_WRITE_LONG)
      case SCSI_WRITE_LONG_10:
      case SCSI_WRITE_LONG_16:
         status = sati_write_long_translate_command(sequence, scsi_io, ata_io);
      break;
#endif // !defined(DISABLE_SATI_WRITE_LONG)

#if !defined(DISABLE_SATI_LOG_SENSE)
      case SCSI_LOG_SENSE:
         status = sati_log_sense_translate_command(sequence, scsi_io, ata_io);
      break;
#endif // !defined(DISABLE_SATI_LOG_SENSE)

      case SCSI_PERSISTENT_RESERVE_IN:
      case SCSI_PERSISTENT_RESERVE_OUT:
         //These commands are not supported by SATI
         sati_scsi_sense_data_construct(
            sequence,
            scsi_io,
            SCSI_STATUS_CHECK_CONDITION,
            SCSI_SENSE_ILLEGAL_REQUEST,
            SCSI_ASC_INVALID_COMMAND_OPERATION_CODE,
            SCSI_ASCQ_INVALID_COMMAND_OPERATION_CODE
         );
         //returning status now to keep sense data set above
         return SATI_FAILURE_CHECK_RESPONSE_DATA;
      break;

#if !defined(DISABLE_SATI_UNMAP)
      case SCSI_UNMAP:
         status = sati_unmap_translate_command(sequence, scsi_io, ata_io);
      break;
#endif // !defined(DISABLE_SATI_UNMAP)

#if !defined(DISABLE_SATI_ATA_PASSTHROUGH)
      case SCSI_ATA_PASSTHRU_12:
          status = sati_passthrough_12_translate_command(sequence, scsi_io, ata_io);
      break;

      case SCSI_ATA_PASSTHRU_16:
          status = sati_passthrough_16_translate_command(sequence, scsi_io, ata_io);
      break;

#endif // !define(DISABLE_SATI_ATA_PASSTHRU)

#if !defined(DISABLE_SATI_READ_BUFFER)
      case SCSI_READ_BUFFER:
         status = sati_read_buffer_translate_command(sequence, scsi_io, ata_io);
      break;
#endif //!defined(DISABLE_SATI_READ_BUFFER)

#if !defined(DISABLE_SATI_WRITE_BUFFER)
      case SCSI_WRITE_BUFFER:
         status = sati_write_buffer_translate_command(sequence, scsi_io, ata_io);
      break;
#endif //!defined(DISABLE_SATI_WRITE_BUFFER)
      default:
         status = SATI_FAILURE_CHECK_RESPONSE_DATA;
      break;
   }

   if( (status == SATI_FAILURE_CHECK_RESPONSE_DATA) &&
       !(sequence->is_sense_response_set) )
   {
      sati_scsi_sense_data_construct(
         sequence,
         scsi_io,
         SCSI_STATUS_CHECK_CONDITION,
         SCSI_SENSE_ILLEGAL_REQUEST,
         SCSI_ASC_INVALID_FIELD_IN_CDB,
         SCSI_ASCQ_INVALID_FIELD_IN_CDB
      );
   }
   return status;
}