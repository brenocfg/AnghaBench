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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
#define  ATA_READ_MULTIPLE 132 
#define  ATA_READ_MULTIPLE_EXT 131 
#define  ATA_WRITE_MULTIPLE 130 
#define  ATA_WRITE_MULTIPLE_EXT 129 
#define  ATA_WRITE_MULTIPLE_FUA_EXT 128 
 int /*<<< orphan*/  FALSE ; 
 int PASSTHROUGH_CDB_COMMAND (int*,int) ; 
 scalar_t__ PASSTHROUGH_CDB_MULTIPLE_COUNT (int*) ; 
 scalar_t__ SCSI_ATA_PASSTHRU_12 ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ sati_get_cdb_byte (int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
BOOL sati_passthrough_multiple_count_error(
   U8 *     cdb
)
{
   U8 ata_command_code;

   if(PASSTHROUGH_CDB_MULTIPLE_COUNT(cdb) > 0)
   {
      if(sati_get_cdb_byte(cdb, 0 ) == SCSI_ATA_PASSTHRU_12)
      {
         ata_command_code = PASSTHROUGH_CDB_COMMAND(cdb, 9);
      }
      else
      {
         ata_command_code = PASSTHROUGH_CDB_COMMAND(cdb, 14);
      }

      switch(ata_command_code)
      {  //MULTICOUNT bit is supported
         case ATA_READ_MULTIPLE:
         case ATA_READ_MULTIPLE_EXT:
         case ATA_WRITE_MULTIPLE:
         case ATA_WRITE_MULTIPLE_EXT:
         case ATA_WRITE_MULTIPLE_FUA_EXT:
            return FALSE;
         break;

         default:
            return TRUE;
      }
   }
   //MULTICOUNT bit is not set
   return FALSE;
}