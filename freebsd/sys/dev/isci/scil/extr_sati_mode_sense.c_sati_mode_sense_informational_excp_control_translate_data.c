#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ U8 ;
typedef  scalar_t__ U32 ;
struct TYPE_9__ {int command_set_supported0; int command_set_enabled0; } ;
struct TYPE_8__ {int /*<<< orphan*/  number_data_bytes_set; } ;
typedef  TYPE_1__ SATI_TRANSLATOR_SEQUENCE_T ;
typedef  TYPE_2__ ATA_IDENTIFY_DEVICE_DATA_T ;

/* Variables and functions */
 int ATA_IDENTIFY_COMMAND_SET_ENABLED0_SMART_ENABLE ; 
 int ATA_IDENTIFY_COMMAND_SET_SUPPORTED0_SMART_ENABLE ; 
 int /*<<< orphan*/  SCSI_MODE_PAGE_INFORMATIONAL_EXCP_CONTROL ; 
 scalar_t__ SCSI_MODE_PAGE_INFORMATIONAL_EXCP_DXCPT_ENABLE ; 
 scalar_t__ SCSI_MODE_SENSE_PC_CURRENT ; 
 scalar_t__ SCSI_MODE_SENSE_PC_SHIFT ; 
 scalar_t__* sati_cb_get_cdb_address (void*) ; 
 scalar_t__ sati_get_cdb_byte (scalar_t__*,int) ; 
 int /*<<< orphan*/  sati_get_data_byte (TYPE_1__*,void*,scalar_t__,scalar_t__*) ; 
 scalar_t__ sati_mode_sense_copy_initial_data (TYPE_1__*,void*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_set_data_byte (TYPE_1__*,void*,scalar_t__,scalar_t__) ; 

U32 sati_mode_sense_informational_excp_control_translate_data(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   ATA_IDENTIFY_DEVICE_DATA_T * identify,
   U32                          offset
)
{
   U8 * cdb          = sati_cb_get_cdb_address(scsi_io);
   U8   page_control = sati_get_cdb_byte(cdb, 2) >> SCSI_MODE_SENSE_PC_SHIFT;
   U32  page_length;

   page_length = sati_mode_sense_copy_initial_data(
                    sequence,
                    scsi_io,
                    offset,
                    page_control,
                    SCSI_MODE_PAGE_INFORMATIONAL_EXCP_CONTROL
                 );

   // If the request queried for the current values, then
   // we need to translate the data from the IDENTIFY DEVICE request.
   if (page_control == SCSI_MODE_SENSE_PC_CURRENT)
   {
      U8 value;

      sati_get_data_byte(sequence, scsi_io, offset+2, &value);

      // Determine if the SMART feature set is supported and enabled.
      if (  (identify->command_set_supported0
                & ATA_IDENTIFY_COMMAND_SET_SUPPORTED0_SMART_ENABLE)
         && (identify->command_set_enabled0
                & ATA_IDENTIFY_COMMAND_SET_ENABLED0_SMART_ENABLE) )
      {
         // Clear the DXCPT field since the SMART feature is supported/enabled.
         value &= ~SCSI_MODE_PAGE_INFORMATIONAL_EXCP_DXCPT_ENABLE;
      }
      else
      {
         // Set the Disable Exception Control (DXCPT) field since the SMART
         // feature is not supported or enabled.
         value |= SCSI_MODE_PAGE_INFORMATIONAL_EXCP_DXCPT_ENABLE;
      }

      sati_set_data_byte(sequence, scsi_io, offset+2, value);

      //This byte has been set twice, the first time in
      //sati_mode_sense_copy_initial_data. number_data_bytes_set
      //needs to be decremented
      sequence->number_data_bytes_set--;
   }

   return page_length;
}