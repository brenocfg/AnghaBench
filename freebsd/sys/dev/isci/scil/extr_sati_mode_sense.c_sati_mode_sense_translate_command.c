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
typedef  scalar_t__ SATI_STATUS ;

/* Variables and functions */
 scalar_t__ SATI_SUCCESS ; 
 int /*<<< orphan*/  sati_ata_identify_device_construct (void*,int /*<<< orphan*/ *) ; 
 scalar_t__ sati_mode_sense_is_page_code_supported (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ sati_mode_sense_is_page_control_supported (int /*<<< orphan*/ *,void*) ; 

SATI_STATUS sati_mode_sense_translate_command(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   void                       * ata_io,
   U8                           cdb_length
)
{
   SATI_STATUS   status;

   /**
    * Validate that the supplied page control (PC) field is supported.
    */
   status = sati_mode_sense_is_page_control_supported(sequence, scsi_io);
   if (status != SATI_SUCCESS)
      return status;

   /**
    * Validate that the supplied page code is supported.
    */
   status = sati_mode_sense_is_page_code_supported(sequence,scsi_io,cdb_length);
   if (status != SATI_SUCCESS)
      return status;

   sati_ata_identify_device_construct(ata_io, sequence);

   return SATI_SUCCESS;
}