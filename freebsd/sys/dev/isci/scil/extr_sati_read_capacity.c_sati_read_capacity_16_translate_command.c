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
struct TYPE_5__ {int allocation_length; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  SATI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  SATI_FAILURE_CHECK_RESPONSE_DATA ; 
 int /*<<< orphan*/  SATI_SEQUENCE_READ_CAPACITY_16 ; 
 int /*<<< orphan*/  SATI_SUCCESS ; 
 int /*<<< orphan*/  SCSI_ASCQ_INVALID_FIELD_IN_CDB ; 
 int /*<<< orphan*/  SCSI_ASC_INVALID_FIELD_IN_CDB ; 
 int SCSI_READ_CAPACITY_PMI_BIT_ENABLE ; 
 int /*<<< orphan*/  SCSI_SENSE_ILLEGAL_REQUEST ; 
 int /*<<< orphan*/  SCSI_STATUS_CHECK_CONDITION ; 
 int /*<<< orphan*/  sati_ata_identify_device_construct (void*,TYPE_1__*) ; 
 int /*<<< orphan*/ * sati_cb_get_cdb_address (void*) ; 
 int sati_get_cdb_byte (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sati_scsi_sense_data_construct (TYPE_1__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

SATI_STATUS sati_read_capacity_16_translate_command(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   void                       * ata_io
)
{
   U8 * cdb = sati_cb_get_cdb_address(scsi_io);

   /**
    * SAT dictates:
    * - the LBA field must be 0
    * - the PMI bit must be 0
    */
   if (
         (
            (sati_get_cdb_byte(cdb, 2) != 0)
         || (sati_get_cdb_byte(cdb, 3) != 0)
         || (sati_get_cdb_byte(cdb, 4) != 0)
         || (sati_get_cdb_byte(cdb, 5) != 0)
         || (sati_get_cdb_byte(cdb, 6) != 0)
         || (sati_get_cdb_byte(cdb, 7) != 0)
         || (sati_get_cdb_byte(cdb, 8) != 0)
         || (sati_get_cdb_byte(cdb, 9) != 0)
         )
         || ((sati_get_cdb_byte(cdb, 14) & SCSI_READ_CAPACITY_PMI_BIT_ENABLE)
              == 1)
      )
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

   // The CDB is properly formed.
   sequence->allocation_length = (sati_get_cdb_byte(cdb, 10) << 24) |
                                 (sati_get_cdb_byte(cdb, 11) << 16) |
                                 (sati_get_cdb_byte(cdb, 12) << 8)  |
                                 (sati_get_cdb_byte(cdb, 13));

   sequence->type              = SATI_SEQUENCE_READ_CAPACITY_16;

   sati_ata_identify_device_construct(ata_io, sequence);
   return SATI_SUCCESS;
}