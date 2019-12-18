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
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  ASL_MSG_READ ; 
 int /*<<< orphan*/  AslAbort () ; 
 TYPE_1__* AslGbl_Files ; 
 int /*<<< orphan*/  FlFileError (size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ feof (int /*<<< orphan*/ ) ; 
 size_t fread (void*,int,size_t,int /*<<< orphan*/ ) ; 

ACPI_STATUS
FlReadFile (
    UINT32                  FileId,
    void                    *Buffer,
    UINT32                  Length)
{
    UINT32                  Actual;


    /* Read and check for error */

    Actual = fread (Buffer, 1, Length, AslGbl_Files[FileId].Handle);
    if (Actual < Length)
    {
        if (feof (AslGbl_Files[FileId].Handle))
        {
            /* End-of-file, just return error */

            return (AE_ERROR);
        }

        FlFileError (FileId, ASL_MSG_READ);
        AslAbort ();
    }

    return (AE_OK);
}