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
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  DT_FIELD ;
typedef  scalar_t__ ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_PARSE ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ * (*) (int /*<<< orphan*/ *)) ; 
 scalar_t__ ACPI_UINT32_MAX ; 
 scalar_t__ AE_NOT_FOUND ; 
 int /*<<< orphan*/  ASL_EOF ; 
 int /*<<< orphan*/  AslAbort () ; 
 int /*<<< orphan*/  AslGbl_CurrentLineBuffer ; 
 scalar_t__ AslGbl_CurrentLineNumber ; 
 scalar_t__ AslGbl_CurrentLineOffset ; 
 int /*<<< orphan*/ * AslGbl_FieldList ; 
 scalar_t__ AslGbl_InputByteCount ; 
 scalar_t__ AslGbl_NextLineOffset ; 
 scalar_t__ CmGetFileSize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DtDumpFieldList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DtGetNextLine (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ DtParseLine (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

DT_FIELD *
DtScanFile (
    FILE                    *Handle)
{
    ACPI_STATUS             Status;
    UINT32                  Offset;


    ACPI_FUNCTION_NAME (DtScanFile);


    /* Get the file size */

    AslGbl_InputByteCount = CmGetFileSize (Handle);
    if (AslGbl_InputByteCount == ACPI_UINT32_MAX)
    {
        AslAbort ();
    }

    AslGbl_CurrentLineNumber = 0;
    AslGbl_CurrentLineOffset = 0;
    AslGbl_NextLineOffset = 0;

    /* Scan line-by-line */

    while ((Offset = DtGetNextLine (Handle, 0)) != ASL_EOF)
    {
        ACPI_DEBUG_PRINT ((ACPI_DB_PARSE, "Line %2.2u/%4.4X - %s",
            AslGbl_CurrentLineNumber, Offset, AslGbl_CurrentLineBuffer));

        Status = DtParseLine (AslGbl_CurrentLineBuffer,
            AslGbl_CurrentLineNumber, Offset);
        if (Status == AE_NOT_FOUND)
        {
            break;
        }
    }

    /* Dump the parse tree if debug enabled */

    DtDumpFieldList (AslGbl_FieldList);
    return (AslGbl_FieldList);
}