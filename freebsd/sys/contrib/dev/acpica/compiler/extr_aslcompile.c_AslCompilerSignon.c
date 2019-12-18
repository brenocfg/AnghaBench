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
typedef  int UINT32 ;

/* Variables and functions */
 char* ACPI_COMMON_HEADER (char*,char*) ; 
 char* AML_DISASSEMBLER_NAME ; 
 char* ASL_COMPILER_NAME ; 
#define  ASL_FILE_ASM_INCLUDE_OUTPUT 133 
#define  ASL_FILE_ASM_SOURCE_OUTPUT 132 
#define  ASL_FILE_C_INCLUDE_OUTPUT 131 
#define  ASL_FILE_C_OFFSET_OUTPUT 130 
#define  ASL_FILE_C_SOURCE_OUTPUT 129 
#define  ASL_FILE_HEX_OUTPUT 128 
 scalar_t__ AcpiGbl_DisasmFlag ; 
 int /*<<< orphan*/  AslGbl_HexOutputFlag ; 
 int /*<<< orphan*/  FlPrintFile (int const,char*,...) ; 
 int /*<<< orphan*/  HEX_OUTPUT_ASL ; 
 int /*<<< orphan*/  HEX_OUTPUT_ASM ; 
 int /*<<< orphan*/  HEX_OUTPUT_C ; 

void
AslCompilerSignon (
    UINT32                  FileId)
{
    char                    *Prefix = "";
    char                    *UtilityName;


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
            FlPrintFile (ASL_FILE_HEX_OUTPUT, "/*\n");
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

    /* Running compiler or disassembler? */

    if (AcpiGbl_DisasmFlag)
    {
        UtilityName = AML_DISASSEMBLER_NAME;
    }
    else
    {
        UtilityName = ASL_COMPILER_NAME;
    }

    /* Compiler signon with copyright */

    FlPrintFile (FileId, "%s\n", Prefix);
    FlPrintFile (FileId, ACPI_COMMON_HEADER (UtilityName, Prefix));
}