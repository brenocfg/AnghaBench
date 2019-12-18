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
typedef  int U32 ;
typedef  int /*<<< orphan*/  SCSI_MODE_SELECT_MODE_PARAMETER_HEADER_6_T ;
typedef  int /*<<< orphan*/  SCSI_MODE_SELECT_MODE_PARAMETER_HEADER_10_T ;

/* Variables and functions */

__attribute__((used)) static
U32 sati_mode_select_get_mode_page_offset(
    U32 block_descriptor_length,
    U32 cdb_size
    )
{
   U32 mode_page_offset;

   if(cdb_size == 6)
   {
      mode_page_offset =  sizeof(SCSI_MODE_SELECT_MODE_PARAMETER_HEADER_6_T) +  block_descriptor_length;
   }
   else if(cdb_size == 10)
   {
      mode_page_offset =  sizeof(SCSI_MODE_SELECT_MODE_PARAMETER_HEADER_10_T) +  block_descriptor_length;
   }
   else
   {
      mode_page_offset = 0;
   }

   return mode_page_offset;
}