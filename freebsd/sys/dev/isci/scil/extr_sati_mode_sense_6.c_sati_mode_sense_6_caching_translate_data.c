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
typedef  scalar_t__ U8 ;
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  ATA_IDENTIFY_DEVICE_DATA_T ;

/* Variables and functions */
 scalar_t__ SCSI_MODE_PAGE_08_LENGTH ; 
 int /*<<< orphan*/  sati_mode_sense_6_translate_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,scalar_t__) ; 
 int /*<<< orphan*/  sati_mode_sense_caching_translate_data (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sati_mode_sense_calculate_page_header (void*,int) ; 

void sati_mode_sense_6_caching_translate_data(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * ata_input_data,
   void                       * scsi_io
)
{
   ATA_IDENTIFY_DEVICE_DATA_T * identify = (ATA_IDENTIFY_DEVICE_DATA_T*)
                                           ata_input_data;
   U8   data_length = (U8) sati_mode_sense_calculate_page_header(scsi_io, 6)
                           + SCSI_MODE_PAGE_08_LENGTH;
   U32  page_offset = sati_mode_sense_6_translate_data(
                         sequence, identify, scsi_io, data_length
                      );

   sati_mode_sense_caching_translate_data(
      sequence, scsi_io, identify, page_offset
   );
}