#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT32 ;
struct TYPE_2__ {char* Filename; int /*<<< orphan*/ * Handle; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ASL_MSG_OPEN ; 
 int /*<<< orphan*/  AslAbort () ; 
 TYPE_1__* AslGbl_Files ; 
 int /*<<< orphan*/  FlFileError (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 

void
FlOpenFile (
    UINT32                  FileId,
    char                    *Filename,
    char                    *Mode)
{
    FILE                    *File;


    AslGbl_Files[FileId].Filename = Filename;
    AslGbl_Files[FileId].Handle = NULL;

    File = fopen (Filename, Mode);
    if (!File)
    {
        FlFileError (FileId, ASL_MSG_OPEN);
        AslAbort ();
    }

    AslGbl_Files[FileId].Handle = File;
}