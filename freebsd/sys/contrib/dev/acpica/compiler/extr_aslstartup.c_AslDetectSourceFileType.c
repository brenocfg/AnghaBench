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
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_3__ {int /*<<< orphan*/  Handle; int /*<<< orphan*/  Filename; } ;
typedef  TYPE_1__ ASL_FILE_INFO ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASL_INPUT_TYPE_ASCII_ASL ; 
 int /*<<< orphan*/  ASL_INPUT_TYPE_ASCII_DATA ; 
 int /*<<< orphan*/  ASL_INPUT_TYPE_BINARY ; 
 int /*<<< orphan*/  ASL_INPUT_TYPE_BINARY_ACPI_TABLE ; 
 int /*<<< orphan*/  AcValidateTableHeader (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* AslGbl_CurrentLineBuffer ; 
 int /*<<< orphan*/  AslGbl_LineBufferSize ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FlIsFileAsciiSource (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ fgets (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strstr (char*,char*) ; 
 scalar_t__ toupper (int) ; 

__attribute__((used)) static UINT8
AslDetectSourceFileType (
    ASL_FILE_INFO           *Info)
{
    char                    *FileChar;
    UINT8                   Type = ASL_INPUT_TYPE_ASCII_DATA; /* default */
    ACPI_STATUS             Status;


    /* Check for 100% ASCII source file (comments are ignored) */

    Status = FlIsFileAsciiSource (Info->Filename, FALSE);
    if (ACPI_SUCCESS (Status))
    {
        /*
         * File contains ASCII source code. Determine if this is an ASL
         * file or an ACPI data table file.
         */
        while (fgets (AslGbl_CurrentLineBuffer, AslGbl_LineBufferSize, Info->Handle))
        {
            /* Uppercase the buffer for caseless compare */

            FileChar = AslGbl_CurrentLineBuffer;
            while (*FileChar)
            {
                *FileChar = (char) toupper ((int) *FileChar);
                FileChar++;
            }

            /* Presence of "DefinitionBlock" indicates actual ASL code */

            if (strstr (AslGbl_CurrentLineBuffer, "DEFINITIONBLOCK"))
            {
                /* Appears to be an ASL file */

                Type = ASL_INPUT_TYPE_ASCII_ASL;
                goto Cleanup;
            }
        }

        /* Appears to be an ASCII data table source file */

        Type = ASL_INPUT_TYPE_ASCII_DATA;
        goto Cleanup;
    }

    /* We have some sort of binary table, check for valid ACPI table */

    fseek (Info->Handle, 0, SEEK_SET);

    Status = AcValidateTableHeader (Info->Handle, 0);
    if (ACPI_SUCCESS (Status))
    {
        fprintf (stderr,
            "Binary file appears to be a valid ACPI table, disassembling\n");

        Type = ASL_INPUT_TYPE_BINARY_ACPI_TABLE;
        goto Cleanup;
    }
    else
    {
        fprintf (stderr,
            "Binary file does not contain a valid ACPI table\n");
    }

    Type = ASL_INPUT_TYPE_BINARY;


Cleanup:

    /* Must seek back to the start of the file */

    fseek (Info->Handle, 0, SEEK_SET);
    return (Type);
}