#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U8 ;
struct TYPE_10__ {int allocation_length; int /*<<< orphan*/  type; TYPE_1__* device; } ;
struct TYPE_9__ {int capabilities; } ;
typedef  TYPE_2__ SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  SATI_STATUS ;
typedef  int /*<<< orphan*/  ATA_SMART_SELF_TEST_LOG_T ;
typedef  int /*<<< orphan*/  ATA_EXTENDED_SMART_SELF_TEST_LOG_T ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_LOG_PAGE_EXTENDED_SMART_SELF_TEST ; 
 int /*<<< orphan*/  ATA_LOG_PAGE_SMART_SELF_TEST ; 
 int /*<<< orphan*/  ATA_SMART_SUB_CMD_RETURN_STATUS ; 
 int /*<<< orphan*/  SATI_COMPLETE ; 
 int SATI_DEVICE_CAP_48BIT_ENABLE ; 
 int SATI_DEVICE_CAP_SMART_ENABLE ; 
 int SATI_DEVICE_CAP_SMART_SELF_TEST_SUPPORT ; 
 int SATI_DEVICE_CAP_SMART_SUPPORT ; 
 int /*<<< orphan*/  SATI_FAILURE ; 
 int /*<<< orphan*/  SATI_FAILURE_CHECK_RESPONSE_DATA ; 
 int SATI_LOG_SENSE_GET_PAGE_CODE (int /*<<< orphan*/ *) ; 
 int SATI_LOG_SENSE_GET_PC_FIELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SATI_SEQUENCE_LOG_SENSE_EXTENDED_SELF_TEST_LOG_PAGE ; 
 int /*<<< orphan*/  SATI_SEQUENCE_LOG_SENSE_INFO_EXCEPTION_LOG_PAGE ; 
 int /*<<< orphan*/  SATI_SEQUENCE_LOG_SENSE_SELF_TEST_LOG_PAGE ; 
 int /*<<< orphan*/  SATI_SEQUENCE_LOG_SENSE_SUPPORTED_LOG_PAGE ; 
 int /*<<< orphan*/  SATI_SUCCESS ; 
 int /*<<< orphan*/  SCSI_ASCQ_ATA_DEVICE_FEATURE_NOT_ENABLED ; 
 int /*<<< orphan*/  SCSI_ASCQ_INVALID_FIELD_IN_CDB ; 
 int /*<<< orphan*/  SCSI_ASCQ_NO_ADDITIONAL_SENSE ; 
 int /*<<< orphan*/  SCSI_ASC_ATA_DEVICE_FEATURE_NOT_ENABLED ; 
 int /*<<< orphan*/  SCSI_ASC_INVALID_FIELD_IN_CDB ; 
 int /*<<< orphan*/  SCSI_ASC_NO_ADDITIONAL_SENSE ; 
#define  SCSI_LOG_PAGE_INFORMATION_EXCEPTION 130 
#define  SCSI_LOG_PAGE_SELF_TEST 129 
#define  SCSI_LOG_PAGE_SUPPORTED_PAGES 128 
 int /*<<< orphan*/  SCSI_SENSE_ABORTED_COMMAND ; 
 int /*<<< orphan*/  SCSI_SENSE_ILLEGAL_REQUEST ; 
 int /*<<< orphan*/  SCSI_STATUS_CHECK_CONDITION ; 
 int /*<<< orphan*/  sati_ata_read_log_ext_construct (void*,TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sati_ata_smart_read_log_construct (void*,TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sati_ata_smart_return_status_construct (void*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sati_cb_get_cdb_address (void*) ; 
 int sati_get_cdb_byte (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sati_scsi_sense_data_construct (TYPE_2__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_supported_log_page_construct (TYPE_2__*,void*) ; 

SATI_STATUS sati_log_sense_translate_command(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   void                       * ata_io
)
{
   U8 * cdb = sati_cb_get_cdb_address(scsi_io);
   SATI_STATUS status = SATI_FAILURE;

   if(SATI_LOG_SENSE_GET_PC_FIELD(cdb) == 1 &&
      (sati_get_cdb_byte(cdb, 3) == 0))
   {
      sequence->allocation_length = (sati_get_cdb_byte(cdb, 7) << 8) |
                                    (sati_get_cdb_byte(cdb, 8));

      switch(SATI_LOG_SENSE_GET_PAGE_CODE(cdb))
      {
         //Return Supported Log Pages log page
         case SCSI_LOG_PAGE_SUPPORTED_PAGES :
            sati_supported_log_page_construct(sequence, scsi_io);
            sequence->type = SATI_SEQUENCE_LOG_SENSE_SUPPORTED_LOG_PAGE;
            status = SATI_COMPLETE;
            break;

         //Return Self-Test Results log page
         case SCSI_LOG_PAGE_SELF_TEST :

            if((sequence->device->capabilities &
               SATI_DEVICE_CAP_SMART_SELF_TEST_SUPPORT) == 0)
            {
               sati_scsi_sense_data_construct(
                  sequence,
                  scsi_io,
                  SCSI_STATUS_CHECK_CONDITION,
                  SCSI_SENSE_ILLEGAL_REQUEST,
                  SCSI_ASC_INVALID_FIELD_IN_CDB,
                  SCSI_ASCQ_INVALID_FIELD_IN_CDB
               );
               status = SATI_FAILURE_CHECK_RESPONSE_DATA;
            }
            else
            {
               //check if 48-bit Address feature set is supported
               if((sequence->device->capabilities &
                  SATI_DEVICE_CAP_48BIT_ENABLE))
               {
                  //ATA Read Log Ext with log address set to 0x07
                  sati_ata_read_log_ext_construct(
                                     ata_io,
                                     sequence,
                                     ATA_LOG_PAGE_EXTENDED_SMART_SELF_TEST,
                                     sizeof(ATA_EXTENDED_SMART_SELF_TEST_LOG_T)
                  );
                  sequence->type =
                            SATI_SEQUENCE_LOG_SENSE_EXTENDED_SELF_TEST_LOG_PAGE;
                  status = SATI_SUCCESS;
               }
               else
               {
                  //ATA Smart Read Log with log address set to 0x06
                  sati_ata_smart_read_log_construct(
                                       ata_io,
                                       sequence,
                                       ATA_LOG_PAGE_SMART_SELF_TEST,
                                       sizeof(ATA_SMART_SELF_TEST_LOG_T)
                  );
                  sequence->type = SATI_SEQUENCE_LOG_SENSE_SELF_TEST_LOG_PAGE;
                  status = SATI_SUCCESS;
               }
            }
            break;

         //Return Informational Exceptions log page
         case SCSI_LOG_PAGE_INFORMATION_EXCEPTION :
            if(sequence->device->capabilities & SATI_DEVICE_CAP_SMART_SUPPORT)
            {
               if(sequence->device->capabilities & SATI_DEVICE_CAP_SMART_ENABLE)
               {
                  sati_ata_smart_return_status_construct(
                                       ata_io,
                                       sequence,
                                       ATA_SMART_SUB_CMD_RETURN_STATUS
                  );
                  sequence->type =
                                SATI_SEQUENCE_LOG_SENSE_INFO_EXCEPTION_LOG_PAGE;
                  status = SATI_SUCCESS;
               }
               else
               {
                  sati_scsi_sense_data_construct(
                     sequence,
                     scsi_io,
                     SCSI_STATUS_CHECK_CONDITION,
                     SCSI_SENSE_ABORTED_COMMAND,
                     SCSI_ASC_ATA_DEVICE_FEATURE_NOT_ENABLED,
                     SCSI_ASCQ_ATA_DEVICE_FEATURE_NOT_ENABLED
                  );

                  status = SATI_FAILURE_CHECK_RESPONSE_DATA;
               }
            }
            else
            {
               sati_scsi_sense_data_construct(
                  sequence,
                  scsi_io,
                  SCSI_STATUS_CHECK_CONDITION,
                  SCSI_SENSE_ILLEGAL_REQUEST,
                  SCSI_ASC_INVALID_FIELD_IN_CDB,
                  SCSI_ASCQ_INVALID_FIELD_IN_CDB
               );

               status = SATI_FAILURE_CHECK_RESPONSE_DATA;
            }
            break;
         default :
            //UNSPECIFIED SATv2r9
            sati_scsi_sense_data_construct(
               sequence,
               scsi_io,
               SCSI_STATUS_CHECK_CONDITION,
               SCSI_SENSE_ILLEGAL_REQUEST,
               SCSI_ASC_NO_ADDITIONAL_SENSE ,
               SCSI_ASCQ_NO_ADDITIONAL_SENSE
            );
            status = SATI_FAILURE_CHECK_RESPONSE_DATA;
            break;
      }
   }
   return status;
}