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
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  ATA_IDENTIFY_DEVICE_DATA_T ;

/* Variables and functions */
 scalar_t__ sati_mode_sense_caching_translate_data (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sati_mode_sense_control_translate_data (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sati_mode_sense_disconnect_reconnect_translate_data (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sati_mode_sense_informational_excp_control_translate_data (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sati_mode_sense_read_write_error_translate_data (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

U32 sati_mode_sense_all_pages_translate_data(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   ATA_IDENTIFY_DEVICE_DATA_T * identify,
   U32                          offset
)
{
   offset += sati_mode_sense_read_write_error_translate_data(
                sequence, scsi_io, identify, offset
             );

   offset += sati_mode_sense_disconnect_reconnect_translate_data(
                sequence, scsi_io, identify, offset
             );

   offset += sati_mode_sense_caching_translate_data(
                sequence, scsi_io, identify, offset
             );

   offset += sati_mode_sense_control_translate_data(
                sequence, scsi_io, identify, offset
             );

   offset += sati_mode_sense_informational_excp_control_translate_data(
                sequence, scsi_io, identify, offset
             );

   return offset;
}