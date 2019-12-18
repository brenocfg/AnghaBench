#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int U32 ;
struct TYPE_6__ {TYPE_1__* device; } ;
struct TYPE_5__ {int capabilities; } ;
typedef  TYPE_2__ SATI_TRANSLATOR_SEQUENCE_T ;

/* Variables and functions */
 int SATI_DEVICE_CAP_SMART_SELF_TEST_SUPPORT ; 
 int SATI_DEVICE_CAP_SMART_SUPPORT ; 
 int SCSI_LOG_PAGE_INFORMATION_EXCEPTION ; 
 int SCSI_LOG_PAGE_SELF_TEST ; 
 int /*<<< orphan*/  sati_set_data_byte (TYPE_2__*,void*,int,int) ; 

__attribute__((used)) static
void sati_supported_log_page_construct(
   SATI_TRANSLATOR_SEQUENCE_T  * sequence,
   void                        * scsi_io
)
{
   U32 next_byte;
   //set SPF = 0 and PAGE_CODE = 0
   sati_set_data_byte(sequence, scsi_io, 0, 0x00);

   //set SUBPAGE_CODE = 0
   sati_set_data_byte(sequence, scsi_io, 1, 0x00);

   //set the Page Length to (n-3) or 2 because only two log pages are supported
   sati_set_data_byte(sequence, scsi_io, 2, 0x00);
   sati_set_data_byte(sequence, scsi_io, 3, 0x02);

   //specify the next byte to be set
   next_byte = 4;

   if(sequence->device->capabilities & SATI_DEVICE_CAP_SMART_SUPPORT)
   {
      sati_set_data_byte(
         sequence,
         scsi_io,
         next_byte,
         SCSI_LOG_PAGE_INFORMATION_EXCEPTION
      );
      next_byte = 5;
   }

   if(sequence->device->capabilities & SATI_DEVICE_CAP_SMART_SELF_TEST_SUPPORT)
   {
      sati_set_data_byte(
         sequence,
         scsi_io,
         next_byte,
         SCSI_LOG_PAGE_SELF_TEST
      );
   }
}