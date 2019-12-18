#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int U8 ;
typedef  scalar_t__ U32 ;
struct TYPE_13__ {scalar_t__ mode_page_offset; scalar_t__ mode_pages_size; scalar_t__ size_of_data_processed; } ;
struct TYPE_11__ {TYPE_6__ process_state; } ;
struct TYPE_12__ {TYPE_1__ command_specific_data; } ;
typedef  TYPE_2__ SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  SATI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  SATI_FAILURE_CHECK_RESPONSE_DATA ; 
#define  SCSI_MODE_PAGE_CACHING 133 
#define  SCSI_MODE_PAGE_CONTROL 132 
#define  SCSI_MODE_PAGE_DISCONNECT_RECONNECT 131 
#define  SCSI_MODE_PAGE_INFORMATIONAL_EXCP_CONTROL 130 
#define  SCSI_MODE_PAGE_POWER_CONDITION 129 
#define  SCSI_MODE_PAGE_READ_WRITE_ERROR 128 
 int SCSI_MODE_SENSE_PAGE_CODE_ENABLE ; 
 int /*<<< orphan*/  sati_get_data_byte (TYPE_2__*,void*,scalar_t__,int*) ; 
 scalar_t__ sati_mode_select_get_mode_page_size (int) ; 
 int /*<<< orphan*/  sati_mode_select_process_mode_page_caching (TYPE_2__*,void*,void*,scalar_t__) ; 
 int /*<<< orphan*/  sati_mode_select_process_mode_page_control (TYPE_2__*,void*,void*,scalar_t__) ; 
 int /*<<< orphan*/  sati_mode_select_process_mode_page_disconnect_reconnect (TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/  sati_mode_select_process_mode_page_informational_exception_control (TYPE_2__*,void*,void*,scalar_t__) ; 
 int /*<<< orphan*/  sati_mode_select_process_mode_page_power_condition (TYPE_2__*,void*,void*,scalar_t__) ; 
 int /*<<< orphan*/  sati_mode_select_process_mode_page_read_write_error_recovery (TYPE_2__*,void*,scalar_t__) ; 

__attribute__((used)) static
SATI_STATUS sati_mode_select_process_mode_page(
   SATI_TRANSLATOR_SEQUENCE_T* sequence,
   void                      * scsi_io,
   void                      * ata_io
)
{
   SATI_STATUS status = SATI_FAILURE_CHECK_RESPONSE_DATA;

   U8 page_code;
   U32 page_size = 0; // in bytes
   U32 size_of_data_to_be_processed;

   U8 page_code_byte;
   U32 mode_page_offset;

   mode_page_offset = sequence->command_specific_data.process_state.mode_page_offset;

   sati_get_data_byte(sequence, scsi_io, mode_page_offset, &page_code_byte);

   // No more pages.
   if(sequence->command_specific_data.process_state.mode_pages_size >
      sequence->command_specific_data.process_state.size_of_data_processed)
   {
      //SCSI_MODE_SENSE_PAGE_CODE_ENABLE==0x3f same for Mode Select
      page_code = page_code_byte & SCSI_MODE_SENSE_PAGE_CODE_ENABLE;
      page_size = sati_mode_select_get_mode_page_size(page_code);
      size_of_data_to_be_processed = sequence->command_specific_data.process_state.mode_pages_size
         - sequence->command_specific_data.process_state.size_of_data_processed;

      if( page_size == 0 )
      {
         status = SATI_FAILURE_CHECK_RESPONSE_DATA;
      }
      else
      {
         // process mode page
         switch(page_code)
         {
         case SCSI_MODE_PAGE_READ_WRITE_ERROR:
            status = sati_mode_select_process_mode_page_read_write_error_recovery(
                        sequence,
                        scsi_io,
                        page_size
                     );
            break;

         case SCSI_MODE_PAGE_DISCONNECT_RECONNECT:
            status = sati_mode_select_process_mode_page_disconnect_reconnect(
                        &sequence->command_specific_data.process_state,
                        page_size
                     );
            break;

         case SCSI_MODE_PAGE_CACHING:
            status = sati_mode_select_process_mode_page_caching(
                        sequence,
                        scsi_io,
                        ata_io,
                        page_size
                     );
            break;

         case SCSI_MODE_PAGE_CONTROL:
            status = sati_mode_select_process_mode_page_control(
                        sequence,
                        scsi_io,
                        ata_io,
                        page_size
                     );
            break;

         case SCSI_MODE_PAGE_INFORMATIONAL_EXCP_CONTROL:
            status = sati_mode_select_process_mode_page_informational_exception_control(
                        sequence,
                        scsi_io,
                        ata_io,
                        page_size
                     );
            break;

         case SCSI_MODE_PAGE_POWER_CONDITION:
            status = sati_mode_select_process_mode_page_power_condition(
                        sequence,
                        scsi_io,
                        ata_io,
                        page_size
                     );

            break;

         default:
            break;
         }

      }
   }

   return status;
}