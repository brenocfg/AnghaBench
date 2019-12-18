#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  char UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_3__ {int /*<<< orphan*/  TableOffset; int /*<<< orphan*/  Value; int /*<<< orphan*/  Name; scalar_t__ Column; int /*<<< orphan*/  ByteOffset; } ;
typedef  TYPE_1__ DT_FIELD ;

/* Variables and functions */
 scalar_t__ AE_OK ; 
 int /*<<< orphan*/  ASL_FILE_INPUT ; 
 int /*<<< orphan*/  ASL_FILE_LISTING_OUTPUT ; 
 int /*<<< orphan*/  AslGbl_ListingFlag ; 
 int /*<<< orphan*/  DtDumpBuffer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FlPrintFile (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ FlReadFile (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  FlSeekFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FlWriteFile (int /*<<< orphan*/ ,char*,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 

void
DtWriteFieldToListing (
    UINT8                   *Buffer,
    DT_FIELD                *Field,
    UINT32                  Length)
{
    UINT8                   FileByte;


    if (!AslGbl_ListingFlag || !Field)
    {
        return;
    }

    /* Dump the original source line */

    FlPrintFile (ASL_FILE_LISTING_OUTPUT, "Input:  ");
    FlSeekFile (ASL_FILE_INPUT, Field->ByteOffset);

    while (FlReadFile (ASL_FILE_INPUT, &FileByte, 1) == AE_OK)
    {
        FlWriteFile (ASL_FILE_LISTING_OUTPUT, &FileByte, 1);
        if (FileByte == '\n')
        {
            break;
        }
    }

    /* Dump the line as parsed and represented internally */

    FlPrintFile (ASL_FILE_LISTING_OUTPUT, "Parsed: %*s : %.64s",
        Field->Column-4, Field->Name, Field->Value);

    if (strlen (Field->Value) > 64)
    {
        FlPrintFile (ASL_FILE_LISTING_OUTPUT, "...Additional data, length 0x%X\n",
            (UINT32) strlen (Field->Value));
    }

    FlPrintFile (ASL_FILE_LISTING_OUTPUT, "\n");

    /* Dump the hex data that will be output for this field */

    DtDumpBuffer (ASL_FILE_LISTING_OUTPUT, Buffer, Field->TableOffset, Length);
}