#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  Filename; } ;
struct TYPE_10__ {char* String; } ;
struct TYPE_11__ {TYPE_1__ Value; } ;
struct TYPE_13__ {TYPE_2__ Asl; } ;
struct TYPE_12__ {char* Dir; struct TYPE_12__* Next; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_3__ ASL_INCLUDE_DIR ;
typedef  TYPE_4__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ASL_ERROR ; 
 size_t ASL_FILE_INPUT ; 
 int /*<<< orphan*/  ASL_FILE_SOURCE_OUTPUT ; 
 int /*<<< orphan*/  ASL_MSG_INCLUDE_FILE_OPEN ; 
 int /*<<< orphan*/  AslCommonError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AslGbl_CurrentColumn ; 
 int /*<<< orphan*/  AslGbl_CurrentLineNumber ; 
 int /*<<< orphan*/  AslGbl_CurrentLineOffset ; 
 char* AslGbl_DirectoryPath ; 
 TYPE_8__* AslGbl_Files ; 
 TYPE_3__* AslGbl_IncludeDirList ; 
 int /*<<< orphan*/  AslGbl_InputByteCount ; 
 int /*<<< orphan*/  AslGbl_LogicalLineNumber ; 
 int /*<<< orphan*/  AslGbl_MsgBuffer ; 
 int /*<<< orphan*/  AslResetCurrentLineBuffer () ; 
 int /*<<< orphan*/ * FlOpenIncludeWithPrefix (char*,TYPE_4__*,char*) ; 
 int /*<<< orphan*/  FlPrintFile (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

void
FlOpenIncludeFile (
    ACPI_PARSE_OBJECT       *Op)
{
    FILE                    *IncludeFile;
    ASL_INCLUDE_DIR         *NextDir;


    /* Op must be valid */

    if (!Op)
    {
        AslCommonError (ASL_ERROR, ASL_MSG_INCLUDE_FILE_OPEN,
            AslGbl_CurrentLineNumber, AslGbl_LogicalLineNumber,
            AslGbl_InputByteCount, AslGbl_CurrentColumn,
            AslGbl_Files[ASL_FILE_INPUT].Filename, " - Null parse node");

        return;
    }

    /*
     * Flush out the "include ()" statement on this line, start
     * the actual include file on the next line
     */
    AslResetCurrentLineBuffer ();
    FlPrintFile (ASL_FILE_SOURCE_OUTPUT, "\n");
    AslGbl_CurrentLineOffset++;


    /* Attempt to open the include file */

    /* If the file specifies an absolute path, just open it */

    if ((Op->Asl.Value.String[0] == '/')  ||
        (Op->Asl.Value.String[0] == '\\') ||
        (Op->Asl.Value.String[1] == ':'))
    {
        IncludeFile = FlOpenIncludeWithPrefix ("", Op, Op->Asl.Value.String);
        if (!IncludeFile)
        {
            goto ErrorExit;
        }
        return;
    }

    /*
     * The include filename is not an absolute path.
     *
     * First, search for the file within the "local" directory -- meaning
     * the same directory that contains the source file.
     *
     * Construct the file pathname from the global directory name.
     */
    IncludeFile = FlOpenIncludeWithPrefix (
        AslGbl_DirectoryPath, Op, Op->Asl.Value.String);
    if (IncludeFile)
    {
        return;
    }

    /*
     * Second, search for the file within the (possibly multiple) directories
     * specified by the -I option on the command line.
     */
    NextDir = AslGbl_IncludeDirList;
    while (NextDir)
    {
        IncludeFile = FlOpenIncludeWithPrefix (
            NextDir->Dir, Op, Op->Asl.Value.String);
        if (IncludeFile)
        {
            return;
        }

        NextDir = NextDir->Next;
    }

    /* We could not open the include file after trying very hard */

ErrorExit:
    sprintf (AslGbl_MsgBuffer, "%s, %s", Op->Asl.Value.String, strerror (errno));
    AslError (ASL_ERROR, ASL_MSG_INCLUDE_FILE_OPEN, Op, AslGbl_MsgBuffer);
}