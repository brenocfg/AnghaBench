#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U8 ;
struct TYPE_7__ {int type; } ;
typedef  TYPE_1__ SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  SATI_STATUS ;

/* Variables and functions */
 int ATA_STATUS_REG_ERROR_BIT ; 
 int /*<<< orphan*/  SATI_COMPLETE ; 
 int /*<<< orphan*/  SATI_FAILURE ; 
 int /*<<< orphan*/  SATI_FAILURE_CHECK_RESPONSE_DATA ; 
#define  SATI_SEQUENCE_LOG_SENSE_EXTENDED_SELF_TEST_LOG_PAGE 130 
#define  SATI_SEQUENCE_LOG_SENSE_INFO_EXCEPTION_LOG_PAGE 129 
#define  SATI_SEQUENCE_LOG_SENSE_SELF_TEST_LOG_PAGE 128 
 int /*<<< orphan*/  SCSI_ASCQ_NO_ADDITIONAL_SENSE ; 
 int /*<<< orphan*/  SCSI_ASC_NO_ADDITIONAL_SENSE ; 
 int /*<<< orphan*/  SCSI_SENSE_ABORTED_COMMAND ; 
 int /*<<< orphan*/  SCSI_STATUS_CHECK_CONDITION ; 
 void* sati_cb_get_ata_data_address (void*) ; 
 int /*<<< orphan*/ * sati_cb_get_d2h_register_fis_address (void*) ; 
 int /*<<< orphan*/  sati_extended_self_test_log_page_construct (TYPE_1__*,void*,void*) ; 
 int sati_get_ata_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sati_information_exception_log_page_contruct (TYPE_1__*,void*,void*) ; 
 int /*<<< orphan*/  sati_scsi_sense_data_construct (TYPE_1__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_self_test_log_page_construct (TYPE_1__*,void*,void*) ; 

SATI_STATUS sati_log_sense_translate_response(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   void                       * ata_io
)
{
   U8 * register_fis = sati_cb_get_d2h_register_fis_address(ata_io);
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

      void * ata_data = sati_cb_get_ata_data_address(ata_io);

      if(ata_data == NULL)
      {
         return SATI_FAILURE;
      }

      switch(sequence->type)
      {
         case SATI_SEQUENCE_LOG_SENSE_EXTENDED_SELF_TEST_LOG_PAGE:
            sati_extended_self_test_log_page_construct(
                                 sequence, scsi_io, ata_data
            );

            status = SATI_COMPLETE;
            break;

         case SATI_SEQUENCE_LOG_SENSE_SELF_TEST_LOG_PAGE:
            sati_self_test_log_page_construct(sequence, scsi_io, ata_data);
            status = SATI_COMPLETE;
            break;

         case SATI_SEQUENCE_LOG_SENSE_INFO_EXCEPTION_LOG_PAGE:
            //This function needs a d->h register fis, not ata data
            sati_information_exception_log_page_contruct(
                                 sequence, scsi_io, ata_io
            );

            status = SATI_COMPLETE;
            break;

         default:
            sati_scsi_sense_data_construct(
               sequence,
               scsi_io,
               SCSI_STATUS_CHECK_CONDITION,
               SCSI_SENSE_ABORTED_COMMAND,
               SCSI_ASC_NO_ADDITIONAL_SENSE ,
               SCSI_ASCQ_NO_ADDITIONAL_SENSE
            );
            status = SATI_FAILURE_CHECK_RESPONSE_DATA;
            break;
      }
   }
   return status;
}