#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {int type; int /*<<< orphan*/  device; } ;
typedef  TYPE_1__ SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  ATA_IDENTIFY_DEVICE_DATA_T ;

/* Variables and functions */
#define  SATI_SEQUENCE_INQUIRY_ATA_INFORMATION 148 
#define  SATI_SEQUENCE_INQUIRY_BLOCK_DEVICE 147 
#define  SATI_SEQUENCE_INQUIRY_DEVICE_ID 146 
#define  SATI_SEQUENCE_INQUIRY_SERIAL_NUMBER 145 
#define  SATI_SEQUENCE_INQUIRY_STANDARD 144 
#define  SATI_SEQUENCE_MODE_SENSE_10_ALL_PAGES 143 
#define  SATI_SEQUENCE_MODE_SENSE_10_CACHING 142 
#define  SATI_SEQUENCE_MODE_SENSE_10_CONTROL 141 
#define  SATI_SEQUENCE_MODE_SENSE_10_DISCONNECT_RECONNECT 140 
#define  SATI_SEQUENCE_MODE_SENSE_10_INFORMATIONAL_EXCP_CONTROL 139 
#define  SATI_SEQUENCE_MODE_SENSE_10_POWER_CONDITION 138 
#define  SATI_SEQUENCE_MODE_SENSE_10_READ_WRITE_ERROR 137 
#define  SATI_SEQUENCE_MODE_SENSE_6_ALL_PAGES 136 
#define  SATI_SEQUENCE_MODE_SENSE_6_CACHING 135 
#define  SATI_SEQUENCE_MODE_SENSE_6_CONTROL 134 
#define  SATI_SEQUENCE_MODE_SENSE_6_DISCONNECT_RECONNECT 133 
#define  SATI_SEQUENCE_MODE_SENSE_6_INFORMATIONAL_EXCP_CONTROL 132 
#define  SATI_SEQUENCE_MODE_SENSE_6_POWER_CONDITION 131 
#define  SATI_SEQUENCE_MODE_SENSE_6_READ_WRITE_ERROR 130 
#define  SATI_SEQUENCE_READ_CAPACITY_10 129 
#define  SATI_SEQUENCE_READ_CAPACITY_16 128 
 int /*<<< orphan*/  sati_device_update_capabilities (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sati_inquiry_ata_information_translate_data (TYPE_1__*,void*,void*) ; 
 int /*<<< orphan*/  sati_inquiry_block_device_translate_data (TYPE_1__*,void*,void*) ; 
 int /*<<< orphan*/  sati_inquiry_device_id_translate_data (TYPE_1__*,void*,void*) ; 
 int /*<<< orphan*/  sati_inquiry_serial_number_translate_data (TYPE_1__*,void*,void*) ; 
 int /*<<< orphan*/  sati_inquiry_standard_translate_data (TYPE_1__*,void*,void*) ; 
 int /*<<< orphan*/  sati_mode_sense_10_all_pages_translate_data (TYPE_1__*,void*,void*) ; 
 int /*<<< orphan*/  sati_mode_sense_10_caching_translate_data (TYPE_1__*,void*,void*) ; 
 int /*<<< orphan*/  sati_mode_sense_10_control_translate_data (TYPE_1__*,void*,void*) ; 
 int /*<<< orphan*/  sati_mode_sense_10_disconnect_reconnect_translate_data (TYPE_1__*,void*,void*) ; 
 int /*<<< orphan*/  sati_mode_sense_10_informational_excp_control_translate_data (TYPE_1__*,void*,void*) ; 
 int /*<<< orphan*/  sati_mode_sense_10_power_condition_translate_data (TYPE_1__*,void*,void*) ; 
 int /*<<< orphan*/  sati_mode_sense_10_read_write_error_translate_data (TYPE_1__*,void*,void*) ; 
 int /*<<< orphan*/  sati_mode_sense_6_all_pages_translate_data (TYPE_1__*,void*,void*) ; 
 int /*<<< orphan*/  sati_mode_sense_6_caching_translate_data (TYPE_1__*,void*,void*) ; 
 int /*<<< orphan*/  sati_mode_sense_6_control_translate_data (TYPE_1__*,void*,void*) ; 
 int /*<<< orphan*/  sati_mode_sense_6_disconnect_reconnect_translate_data (TYPE_1__*,void*,void*) ; 
 int /*<<< orphan*/  sati_mode_sense_6_informational_excp_control_translate_data (TYPE_1__*,void*,void*) ; 
 int /*<<< orphan*/  sati_mode_sense_6_power_condition_translate_data (TYPE_1__*,void*,void*) ; 
 int /*<<< orphan*/  sati_mode_sense_6_read_write_error_translate_data (TYPE_1__*,void*,void*) ; 
 int /*<<< orphan*/  sati_read_capacity_10_translate_data (TYPE_1__*,void*,void*) ; 
 int /*<<< orphan*/  sati_read_capacity_16_translate_data (TYPE_1__*,void*,void*) ; 

__attribute__((used)) static
void sati_translate_data(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * ata_input_data,
   void                       * scsi_io
)
{
   // Update the device capabilities in the odd/crazy event something changed.
   sati_device_update_capabilities(
      sequence->device, (ATA_IDENTIFY_DEVICE_DATA_T*) ata_input_data
   );

   // Look at the first byte to determine the SCSI command to translate.
   switch (sequence->type)
   {
#if !defined(DISABLE_SATI_INQUIRY)
      case SATI_SEQUENCE_INQUIRY_STANDARD:
         sati_inquiry_standard_translate_data(
            sequence, ata_input_data, scsi_io
         );
      break;

      case SATI_SEQUENCE_INQUIRY_SERIAL_NUMBER:
         sati_inquiry_serial_number_translate_data(
            sequence, ata_input_data, scsi_io
         );
      break;

      case SATI_SEQUENCE_INQUIRY_DEVICE_ID:
         sati_inquiry_device_id_translate_data(
            sequence, ata_input_data, scsi_io
         );
      break;

      case SATI_SEQUENCE_INQUIRY_BLOCK_DEVICE:
         sati_inquiry_block_device_translate_data(
            sequence, ata_input_data, scsi_io
         );
      break;

      case SATI_SEQUENCE_INQUIRY_ATA_INFORMATION:
         sati_inquiry_ata_information_translate_data(
            sequence, ata_input_data, scsi_io
         );
      break;

#endif // !defined(DISABLE_SATI_INQUIRY)

#if !defined(DISABLE_SATI_READ_CAPACITY)
      case SATI_SEQUENCE_READ_CAPACITY_10:
         sati_read_capacity_10_translate_data(sequence, ata_input_data, scsi_io);
      break;

      case SATI_SEQUENCE_READ_CAPACITY_16:
         sati_read_capacity_16_translate_data(sequence, ata_input_data, scsi_io);
      break;
#endif // !defined(DISABLE_SATI_READ_CAPACITY)

#if !defined(DISABLE_SATI_MODE_SENSE)
      case SATI_SEQUENCE_MODE_SENSE_6_CACHING:
         sati_mode_sense_6_caching_translate_data(
            sequence, ata_input_data, scsi_io
         );
      break;

      case SATI_SEQUENCE_MODE_SENSE_6_INFORMATIONAL_EXCP_CONTROL:
         sati_mode_sense_6_informational_excp_control_translate_data(
            sequence, ata_input_data, scsi_io
         );
      break;

      case SATI_SEQUENCE_MODE_SENSE_6_READ_WRITE_ERROR:
         sati_mode_sense_6_read_write_error_translate_data(
            sequence, ata_input_data, scsi_io
         );
      break;

      case SATI_SEQUENCE_MODE_SENSE_6_DISCONNECT_RECONNECT:
         sati_mode_sense_6_disconnect_reconnect_translate_data(
            sequence, ata_input_data, scsi_io
         );
      break;

      case SATI_SEQUENCE_MODE_SENSE_6_CONTROL:
         sati_mode_sense_6_control_translate_data(
            sequence, ata_input_data, scsi_io
         );
      break;

      case SATI_SEQUENCE_MODE_SENSE_6_ALL_PAGES:
         sati_mode_sense_6_all_pages_translate_data(
            sequence, ata_input_data, scsi_io
         );
      break;

      case SATI_SEQUENCE_MODE_SENSE_6_POWER_CONDITION:
         sati_mode_sense_6_power_condition_translate_data(
            sequence, ata_input_data, scsi_io
         );
      break;

      case SATI_SEQUENCE_MODE_SENSE_10_POWER_CONDITION:
         sati_mode_sense_10_power_condition_translate_data(
            sequence, ata_input_data, scsi_io
         );
      break;

      case SATI_SEQUENCE_MODE_SENSE_10_CACHING:
         sati_mode_sense_10_caching_translate_data(
            sequence, ata_input_data, scsi_io
         );
      break;

      case SATI_SEQUENCE_MODE_SENSE_10_INFORMATIONAL_EXCP_CONTROL:
         sati_mode_sense_10_informational_excp_control_translate_data(
            sequence, ata_input_data, scsi_io
         );
      break;

      case SATI_SEQUENCE_MODE_SENSE_10_READ_WRITE_ERROR:
         sati_mode_sense_10_read_write_error_translate_data(
            sequence, ata_input_data, scsi_io
         );
      break;

      case SATI_SEQUENCE_MODE_SENSE_10_DISCONNECT_RECONNECT:
         sati_mode_sense_10_disconnect_reconnect_translate_data(
            sequence, ata_input_data, scsi_io
         );
      break;

      case SATI_SEQUENCE_MODE_SENSE_10_CONTROL:
         sati_mode_sense_10_control_translate_data(
            sequence, ata_input_data, scsi_io
         );
      break;

      case SATI_SEQUENCE_MODE_SENSE_10_ALL_PAGES:
         sati_mode_sense_10_all_pages_translate_data(
            sequence, ata_input_data, scsi_io
         );
      break;
#endif // !defined(DISABLE_SATI_MODE_SENSE)

      default:
      break;
   }
}