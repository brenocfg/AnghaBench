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
typedef  size_t U16 ;
typedef  int /*<<< orphan*/  SATI_TRANSLATOR_SEQUENCE_T ;

/* Variables and functions */
 scalar_t__ SCSI_MODE_SENSE_PC_CHANGEABLE ; 
 int /*<<< orphan*/ * sat_changeable_mode_pages ; 
 int /*<<< orphan*/ * sat_default_mode_pages ; 
 int /*<<< orphan*/ * sat_mode_page_sizes ; 
 int /*<<< orphan*/  sati_copy_data (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t sati_mode_page_get_page_index (scalar_t__) ; 

U32 sati_mode_sense_copy_initial_data(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   U32                          page_start,
   U8                           page_control,
   U8                           page_code
)
{
   U16 page_index  = sati_mode_page_get_page_index(page_code);
   U32 page_length = sat_mode_page_sizes[page_index];

   // Find out if the current values are requested or if the default
   // values are being requested.
   if (page_control == SCSI_MODE_SENSE_PC_CHANGEABLE)
   {
      // Copy the changeable mode page information.
      sati_copy_data(
         sequence,
         scsi_io,
         page_start,
         sat_changeable_mode_pages[page_index],
         page_length
      );
   }
   else
   {
      // Copy the default static values template to the user data area.
      sati_copy_data(
         sequence,
         scsi_io,
         page_start,
         sat_default_mode_pages[page_index],
         page_length
      );
   }

   return page_length;
}