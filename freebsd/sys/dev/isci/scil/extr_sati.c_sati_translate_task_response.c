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
typedef  int U8 ;
struct TYPE_5__ {int type; } ;
typedef  TYPE_1__ SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  SATI_STATUS ;

/* Variables and functions */
 int ATA_STATUS_REG_DEVICE_FAULT_BIT ; 
 int ATA_STATUS_REG_ERROR_BIT ; 
 int /*<<< orphan*/  SATI_COMPLETE ; 
 int /*<<< orphan*/  SATI_FAILURE ; 
 int /*<<< orphan*/  SATI_FAILURE_CHECK_RESPONSE_DATA ; 
 int /*<<< orphan*/  SATI_FAILURE_INVALID_SEQUENCE_TYPE ; 
#define  SATI_SEQUENCE_ABORT_TASK_SET 129 
#define  SATI_SEQUENCE_LUN_RESET 128 
 int /*<<< orphan*/  SCSI_TASK_MGMT_FUNC_COMPLETE ; 
 int /*<<< orphan*/  SCSI_TASK_MGMT_FUNC_FAILED ; 
 int /*<<< orphan*/  sati_abort_task_set_translate_data (TYPE_1__*,void*,void*) ; 
 void* sati_cb_get_ata_data_address (void*) ; 
 int* sati_cb_get_d2h_register_fis_address (void*) ; 
 scalar_t__ sati_get_ata_status (int*) ; 
 int /*<<< orphan*/  sati_scsi_response_data_construct (TYPE_1__*,void*,int /*<<< orphan*/ ) ; 

SATI_STATUS sati_translate_task_response(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   void                       * ata_io
)
{
   SATI_STATUS   status       = SATI_FAILURE_CHECK_RESPONSE_DATA;
   U8          * register_fis = sati_cb_get_d2h_register_fis_address(ata_io);
   U8            ata_status;

   /**
    * If the device fault bit is set in the status register, then
    * set the sense data and return.
    */
   ata_status = (U8) sati_get_ata_status(register_fis);
   if (ata_status & ATA_STATUS_REG_DEVICE_FAULT_BIT)
   {
      sati_scsi_response_data_construct(
         sequence,
         scsi_io,
         SCSI_TASK_MGMT_FUNC_FAILED
      );
      return SATI_FAILURE_CHECK_RESPONSE_DATA;
   }

   // Look at the sequence type to determine the response translation method
   // to invoke.
   switch (sequence->type)
   {
      case SATI_SEQUENCE_LUN_RESET:
         if (ata_status & ATA_STATUS_REG_ERROR_BIT)
         {
            sati_scsi_response_data_construct(
               sequence, scsi_io, SCSI_TASK_MGMT_FUNC_FAILED);
         }
         else
         {
            sati_scsi_response_data_construct(
               sequence, scsi_io, SCSI_TASK_MGMT_FUNC_COMPLETE);
         }

         status = SATI_COMPLETE;
      break;

#if !defined(DISABLE_SATI_ABORT_TASK_SET)
      case SATI_SEQUENCE_ABORT_TASK_SET:
         if (ata_status & ATA_STATUS_REG_ERROR_BIT)
         {
            sati_scsi_response_data_construct(
               sequence, scsi_io, SCSI_TASK_MGMT_FUNC_FAILED);
         }
         else
         {
            void * ata_data = sati_cb_get_ata_data_address(ata_io);

            if(ata_data == NULL)
            {
               status = SATI_FAILURE;
            }
            else
            {
               status = sati_abort_task_set_translate_data(
                           sequence,
                           ata_data,
                           scsi_io
                        );
            }
         }
      break;
#endif // !defined(DISABLE_SATI_ABORT_TASK_SET)

      default:
         status = SATI_FAILURE_INVALID_SEQUENCE_TYPE;
      break;
   }

   return status;
}