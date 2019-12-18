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
typedef  int U8 ;
typedef  int /*<<< orphan*/  SATI_TRANSLATOR_SEQUENCE_T ;

/* Variables and functions */
 int SCSI_ASC_NO_ADDITIONAL_SENSE ; 
 int SCSI_DIAGNOSTIC_FAILURE_ON_COMPONENT ; 
 int SCSI_SENSE_ABORTED_COMMAND ; 
 int SCSI_SENSE_HARDWARE_ERROR ; 
 int SCSI_SENSE_MEDIUM_ERROR ; 
 int SCSI_SENSE_NO_SENSE ; 
 int /*<<< orphan*/  sati_set_data_byte (int /*<<< orphan*/ *,void*,int,int) ; 

__attribute__((used)) static
void sati_translate_sense_values(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   U8                           self_test_status_byte
)
{
   //byte 17
   sati_set_data_byte(
      sequence,
      scsi_io,
      21,
      SCSI_DIAGNOSTIC_FAILURE_ON_COMPONENT
   );

   switch(self_test_status_byte)
   {
      case 1:
         //byte 16
         sati_set_data_byte(sequence, scsi_io, 20, SCSI_SENSE_ABORTED_COMMAND);

         //byte 18
         sati_set_data_byte(sequence, scsi_io, 22, 0x81);
         break;

      case 2:
         //byte 16
         sati_set_data_byte(sequence, scsi_io, 20, SCSI_SENSE_ABORTED_COMMAND);

         //byte 18
         sati_set_data_byte(sequence, scsi_io, 22, 0x82);
         break;

      case 3:
         //byte 16
         sati_set_data_byte(sequence, scsi_io, 20, SCSI_SENSE_ABORTED_COMMAND);

         //byte 18
         sati_set_data_byte(sequence, scsi_io, 22, 0x83);
         break;

      case 4:
         //byte 16
         sati_set_data_byte(sequence, scsi_io, 20, SCSI_SENSE_HARDWARE_ERROR);

         //byte 18
         sati_set_data_byte(sequence, scsi_io, 22, 0x84);
         break;

      case 5:
         //byte 16
         sati_set_data_byte(sequence, scsi_io, 20, SCSI_SENSE_HARDWARE_ERROR);

         //byte 18
         sati_set_data_byte(sequence, scsi_io, 22, 0x85);
         break;

      case 6:
         //byte 16
         sati_set_data_byte(sequence, scsi_io, 20, SCSI_SENSE_HARDWARE_ERROR);

         //byte 18
         sati_set_data_byte(sequence, scsi_io, 22, 0x86);
         break;

      case 7:
         //byte 16
         sati_set_data_byte(sequence, scsi_io, 20, SCSI_SENSE_MEDIUM_ERROR);

         //byte 18
         sati_set_data_byte(sequence, scsi_io, 22, 0x87);
         break;

      case 8:
         //byte 16
         sati_set_data_byte(sequence, scsi_io, 20, SCSI_SENSE_HARDWARE_ERROR);

         //byte 18
         sati_set_data_byte(sequence, scsi_io, 22, 0x88);
         break;

      default:
         //byte 16
         sati_set_data_byte(sequence, scsi_io, 20, SCSI_SENSE_NO_SENSE);
         //byte 17
         sati_set_data_byte(sequence, scsi_io, 21, SCSI_ASC_NO_ADDITIONAL_SENSE);
         //byte 18
         sati_set_data_byte(sequence, scsi_io, 22, 0x00);
         break;
   }

}