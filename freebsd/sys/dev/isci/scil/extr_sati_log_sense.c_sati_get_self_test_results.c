#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t U16 ;
struct TYPE_7__ {TYPE_2__* descriptor_entrys; int /*<<< orphan*/ * self_test_descriptor_index; } ;
struct TYPE_5__ {int status_byte; int time_stamp_high; int time_stamp_low; int failing_lba_high_ext; int failing_lba_mid_ext; int failing_lba_low_ext; int failing_lba_high; int failing_lba_mid; int failing_lba_low; } ;
struct TYPE_6__ {TYPE_1__ DESCRIPTOR_ENTRY; } ;
typedef  int /*<<< orphan*/  SATI_TRANSLATOR_SEQUENCE_T ;
typedef  TYPE_3__ ATA_EXTENDED_SMART_SELF_TEST_LOG_T ;

/* Variables and functions */
 int /*<<< orphan*/  sati_set_data_byte (int /*<<< orphan*/ *,void*,int,int) ; 
 int /*<<< orphan*/  sati_set_parameters_to_zero (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  sati_translate_sense_values (int /*<<< orphan*/ *,void*,int) ; 

__attribute__((used)) static
void sati_get_self_test_results(
   SATI_TRANSLATOR_SEQUENCE_T          * sequence,
   void                                * scsi_io,
   ATA_EXTENDED_SMART_SELF_TEST_LOG_T  * ata_log
)
{
   U16 descriptor_index = *((U16 *)(&ata_log->self_test_descriptor_index[0]));

   /*
    * SATv2 wants data from descriptor N where N is equal to
    * (descriptor_index - parameter_code) + 1. Since parameter
    * code is always 0x0001 just checking descriptor_index.
    */

   if(descriptor_index <= 0)
   {
      sati_set_parameters_to_zero(sequence, scsi_io);
   }
   else
   {
      sati_set_data_byte(
       sequence,
       scsi_io,
       8,
       ata_log->descriptor_entrys[descriptor_index].DESCRIPTOR_ENTRY.status_byte
      );

      //Sef-test number unspecified per satv2
      sati_set_data_byte(sequence, scsi_io, 9, 0x00);
      sati_set_data_byte(
       sequence,
       scsi_io,
       10,
       ata_log->descriptor_entrys[descriptor_index].DESCRIPTOR_ENTRY.time_stamp_high
      );

      sati_set_data_byte(
       sequence,
       scsi_io,
       11,
       ata_log->descriptor_entrys[descriptor_index].DESCRIPTOR_ENTRY.time_stamp_low
      );

      //set to zero because it's a 48bit address
      sati_set_data_byte(sequence, scsi_io, 12, 0x00);
      sati_set_data_byte(sequence, scsi_io, 13, 0x00);

      sati_set_data_byte(
       sequence,
       scsi_io,
       14,
       ata_log->descriptor_entrys[descriptor_index].DESCRIPTOR_ENTRY.failing_lba_high_ext
      );

      sati_set_data_byte(
       sequence,
       scsi_io,
       15,
       ata_log->descriptor_entrys[descriptor_index].DESCRIPTOR_ENTRY.failing_lba_mid_ext
      );

      sati_set_data_byte(
       sequence,
       scsi_io,
       16,
       ata_log->descriptor_entrys[descriptor_index].DESCRIPTOR_ENTRY.failing_lba_low_ext
      );

      sati_set_data_byte(
       sequence,
       scsi_io,
       17,
       ata_log->descriptor_entrys[descriptor_index].DESCRIPTOR_ENTRY.failing_lba_high
      );

      sati_set_data_byte(
       sequence,
       scsi_io,
       18,
       ata_log->descriptor_entrys[descriptor_index].DESCRIPTOR_ENTRY.failing_lba_mid
      );

      sati_set_data_byte(
       sequence,
       scsi_io,
       19,
       ata_log->descriptor_entrys[descriptor_index].DESCRIPTOR_ENTRY.failing_lba_low
      );

      sati_translate_sense_values(
       sequence,
       scsi_io,
       ata_log->descriptor_entrys[descriptor_index].DESCRIPTOR_ENTRY.status_byte
      );
   }
}