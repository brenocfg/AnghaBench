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
typedef  int /*<<< orphan*/  U32 ;

/* Variables and functions */
 int /*<<< orphan*/  SCSI_MODE_PAGE_01_LENGTH ; 
 int /*<<< orphan*/  SCSI_MODE_PAGE_02_LENGTH ; 
 int /*<<< orphan*/  SCSI_MODE_PAGE_08_LENGTH ; 
 int /*<<< orphan*/  SCSI_MODE_PAGE_0A_LENGTH ; 
 int /*<<< orphan*/  SCSI_MODE_PAGE_1A_LENGTH ; 
 int /*<<< orphan*/  SCSI_MODE_PAGE_1C_LENGTH ; 
#define  SCSI_MODE_PAGE_CACHING 133 
#define  SCSI_MODE_PAGE_CONTROL 132 
#define  SCSI_MODE_PAGE_DISCONNECT_RECONNECT 131 
#define  SCSI_MODE_PAGE_INFORMATIONAL_EXCP_CONTROL 130 
#define  SCSI_MODE_PAGE_POWER_CONDITION 129 
#define  SCSI_MODE_PAGE_READ_WRITE_ERROR 128 

__attribute__((used)) static
U32 sati_mode_select_get_mode_page_size(
   U8 page_code
)
{
   U32 page_size=0;

   switch (page_code)
   {
   case SCSI_MODE_PAGE_READ_WRITE_ERROR:
      page_size=SCSI_MODE_PAGE_01_LENGTH;
      break;

   case SCSI_MODE_PAGE_DISCONNECT_RECONNECT:
      page_size=SCSI_MODE_PAGE_02_LENGTH;
      break;

   case SCSI_MODE_PAGE_CACHING:
      page_size=SCSI_MODE_PAGE_08_LENGTH;
      break;

   case SCSI_MODE_PAGE_CONTROL:
      page_size=SCSI_MODE_PAGE_0A_LENGTH;
      break;

   case SCSI_MODE_PAGE_INFORMATIONAL_EXCP_CONTROL:
      page_size=SCSI_MODE_PAGE_1C_LENGTH;
      break;

   case SCSI_MODE_PAGE_POWER_CONDITION:
      page_size=SCSI_MODE_PAGE_1A_LENGTH;
      break;
   default:
      page_size=0;
      break;
   }

   return page_size;
}