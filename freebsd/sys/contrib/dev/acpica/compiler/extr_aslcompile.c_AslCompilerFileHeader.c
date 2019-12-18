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
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;
typedef  int UINT32 ;
struct TYPE_2__ {int /*<<< orphan*/  Filename; } ;

/* Variables and functions */
#define  ASL_FILE_ASM_INCLUDE_OUTPUT 133 
#define  ASL_FILE_ASM_SOURCE_OUTPUT 132 
#define  ASL_FILE_C_INCLUDE_OUTPUT 131 
#define  ASL_FILE_C_OFFSET_OUTPUT 130 
#define  ASL_FILE_C_SOURCE_OUTPUT 129 
#define  ASL_FILE_HEX_OUTPUT 128 
 size_t ASL_FILE_INPUT ; 
 TYPE_1__* AslGbl_Files ; 
 int /*<<< orphan*/  AslGbl_HexOutputFlag ; 
 int /*<<< orphan*/  FlPrintFile (int,char*,...) ; 
 int /*<<< orphan*/  HEX_OUTPUT_ASL ; 
 int /*<<< orphan*/  HEX_OUTPUT_ASM ; 
 int /*<<< orphan*/  HEX_OUTPUT_C ; 
 int /*<<< orphan*/  asctime (struct tm*) ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

void
AslCompilerFileHeader (
    UINT32                  FileId)
{
    struct tm               *NewTime;
    time_t                  Aclock;
    char                    *Prefix = "";


    /* Set line prefix depending on the destination file type */

    switch (FileId)
    {
    case ASL_FILE_ASM_SOURCE_OUTPUT:
    case ASL_FILE_ASM_INCLUDE_OUTPUT:

        Prefix = "; ";
        break;

    case ASL_FILE_HEX_OUTPUT:

        if (AslGbl_HexOutputFlag == HEX_OUTPUT_ASM)
        {
            Prefix = "; ";
        }
        else if ((AslGbl_HexOutputFlag == HEX_OUTPUT_C) ||
                 (AslGbl_HexOutputFlag == HEX_OUTPUT_ASL))
        {
            Prefix = " * ";
        }
        break;

    case ASL_FILE_C_SOURCE_OUTPUT:
    case ASL_FILE_C_OFFSET_OUTPUT:
    case ASL_FILE_C_INCLUDE_OUTPUT:

        Prefix = " * ";
        break;

    default:

        /* No other output types supported */

        break;
    }

    /* Compilation header with timestamp */

    (void) time (&Aclock);
    NewTime = localtime (&Aclock);

    FlPrintFile (FileId,
        "%sCompilation of \"%s\" - %s%s\n",
        Prefix, AslGbl_Files[ASL_FILE_INPUT].Filename, asctime (NewTime),
        Prefix);

    switch (FileId)
    {
    case ASL_FILE_C_SOURCE_OUTPUT:
    case ASL_FILE_C_OFFSET_OUTPUT:
    case ASL_FILE_C_INCLUDE_OUTPUT:

        FlPrintFile (FileId, " */\n");
        break;

    default:

        /* Nothing to do for other output types */

        break;
    }
}