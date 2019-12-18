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
 size_t ASL_FILE_PREPROCESSOR ; 
 size_t ASL_FILE_PREPROCESSOR_USER ; 
 int /*<<< orphan*/  ASL_MSG_WRITE ; 
 int /*<<< orphan*/  AslAbort () ; 
 TYPE_1__* AslGbl_Files ; 
 scalar_t__ AslGbl_PreprocessorOutputFlag ; 
 int /*<<< orphan*/  FlFileError (size_t,int /*<<< orphan*/ ) ; 
 size_t fwrite (char*,int,size_t,int /*<<< orphan*/ ) ; 

void
FlWriteFile (
    UINT32                  FileId,
    void                    *Buffer,
    UINT32                  Length)
{
    UINT32                  Actual;


    /* Write and check for error */

    Actual = fwrite ((char *) Buffer, 1, Length, AslGbl_Files[FileId].Handle);
    if (Actual != Length)
    {
        FlFileError (FileId, ASL_MSG_WRITE);
        AslAbort ();
    }

    if ((FileId == ASL_FILE_PREPROCESSOR) && AslGbl_PreprocessorOutputFlag)
    {
        /* Duplicate the output to the user preprocessor (.i) file */

        Actual = fwrite ((char *) Buffer, 1, Length,
            AslGbl_Files[ASL_FILE_PREPROCESSOR_USER].Handle);
        if (Actual != Length)
        {
            FlFileError (FileId, ASL_MSG_WRITE);
            AslAbort ();
        }
    }
}