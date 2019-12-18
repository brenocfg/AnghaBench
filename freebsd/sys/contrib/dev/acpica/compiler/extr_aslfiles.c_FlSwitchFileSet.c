#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* Filename; } ;
struct TYPE_4__ {struct TYPE_4__* Next; int /*<<< orphan*/  TableId; int /*<<< orphan*/  TableSignature; TYPE_3__* Files; } ;
typedef  TYPE_1__ ASL_GLOBAL_FILE_NODE ;
typedef  int /*<<< orphan*/  ASL_FILE_SWITCH_STATUS ;

/* Variables and functions */
 size_t ASL_FILE_INPUT ; 
 TYPE_3__* AslGbl_Files ; 
 TYPE_1__* AslGbl_FilesList ; 
 int /*<<< orphan*/  AslGbl_TableId ; 
 int /*<<< orphan*/  AslGbl_TableSignature ; 
 int /*<<< orphan*/  FILE_NOT_FOUND ; 
 int /*<<< orphan*/  SWITCH_TO_DIFFERENT_FILE ; 
 int /*<<< orphan*/  SWITCH_TO_SAME_FILE ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

ASL_FILE_SWITCH_STATUS
FlSwitchFileSet (
    char                    *InputFilename)
{
    ASL_GLOBAL_FILE_NODE    *Current = AslGbl_FilesList;
    char                    *PrevFilename = Current->Files[ASL_FILE_INPUT].Filename;


    while (Current)
    {
        if (!strcmp(Current->Files[ASL_FILE_INPUT].Filename, InputFilename))
        {
            AslGbl_Files = Current->Files;
            AslGbl_TableSignature = Current->TableSignature;
            AslGbl_TableId = Current->TableId;

            if (!strcmp (InputFilename, PrevFilename))
            {
                return (SWITCH_TO_SAME_FILE);
            }
            else
            {
                return (SWITCH_TO_DIFFERENT_FILE);
            }
        }

        Current = Current->Next;
    }

    return (FILE_NOT_FOUND);
}