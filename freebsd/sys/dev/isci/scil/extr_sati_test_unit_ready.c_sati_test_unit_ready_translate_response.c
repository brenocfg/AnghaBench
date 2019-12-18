#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  U8 ;
typedef  int /*<<< orphan*/  SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  SATI_STATUS ;

/* Variables and functions */
 int ATA_STATUS_REG_ERROR_BIT ; 
 int /*<<< orphan*/  SATI_COMPLETE ; 
 int /*<<< orphan*/  SATI_FAILURE_CHECK_RESPONSE_DATA ; 
 int /*<<< orphan*/  SCSI_ASCQ_LUN_NOT_RESPOND_TO_SELECTION ; 
 int /*<<< orphan*/  SCSI_ASC_LUN_NOT_RESPOND_TO_SELECTION ; 
 int /*<<< orphan*/  SCSI_SENSE_NOT_READY ; 
 int /*<<< orphan*/  SCSI_STATUS_CHECK_CONDITION ; 
 int /*<<< orphan*/ * sati_cb_get_d2h_register_fis_address (void*) ; 
 int sati_get_ata_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sati_scsi_sense_data_construct (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

SATI_STATUS sati_test_unit_ready_translate_response(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   void                       * ata_io
)
{
   U8 * register_fis = sati_cb_get_d2h_register_fis_address(ata_io);

   /**
    * SAT dictates:
    * - If the ATA CHECK POWER MODE command returns an error, then
    *   return sense data indicating the LOGICAL UNIT DOES NOT RESPONSE
    *   TO SELECTION.
    * - All other cases are considered successful.
    */
   if (sati_get_ata_status(register_fis) & ATA_STATUS_REG_ERROR_BIT)
   {
      sati_scsi_sense_data_construct(
         sequence,
         scsi_io,
         SCSI_STATUS_CHECK_CONDITION,
         SCSI_SENSE_NOT_READY,
         SCSI_ASC_LUN_NOT_RESPOND_TO_SELECTION,
         SCSI_ASCQ_LUN_NOT_RESPOND_TO_SELECTION
      );
      return SATI_FAILURE_CHECK_RESPONSE_DATA;
   }

   return SATI_COMPLETE;
}