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
struct TYPE_2__ {int /*<<< orphan*/  Handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASL_MSG_SEEK ; 
 int /*<<< orphan*/  AslAbort () ; 
 TYPE_1__* AslGbl_Files ; 
 int /*<<< orphan*/  FlFileError (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int fseek (int /*<<< orphan*/ ,long,int /*<<< orphan*/ ) ; 

void
FlSeekFile (
    UINT32                  FileId,
    long                    Offset)
{
    int                     Error;


    Error = fseek (AslGbl_Files[FileId].Handle, Offset, SEEK_SET);
    if (Error)
    {
        FlFileError (FileId, ASL_MSG_SEEK);
        AslAbort ();
    }
}