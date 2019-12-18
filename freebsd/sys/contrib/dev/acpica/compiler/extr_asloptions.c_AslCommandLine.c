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
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 char* ACPI_COMMON_SIGNON (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASL_COMPILER_NAME ; 
 int /*<<< orphan*/  AcpiGbl_DisasmFlag ; 
 size_t AcpiGbl_Optind ; 
 int AslDoOptions (int,char**,int /*<<< orphan*/ ) ; 
 scalar_t__ AslGbl_DoSignon ; 
 scalar_t__ AslGbl_DoTemplates ; 
 scalar_t__ AslGbl_IgnoreErrors ; 
 int /*<<< orphan*/  DtCreateTemplates (char**) ; 
 int /*<<< orphan*/  FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  Usage () ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*) ; 

int
AslCommandLine (
    int                     argc,
    char                    **argv)
{
    int                     BadCommandLine = 0;
    ACPI_STATUS             Status;


    /* Minimum command line contains at least the command and an input file */

    if (argc < 2)
    {
        Usage ();
        exit (1);
    }

    /* Process all command line options */

    BadCommandLine = AslDoOptions (argc, argv, FALSE);

    if (AslGbl_DoTemplates)
    {
        Status = DtCreateTemplates (argv);
        if (ACPI_FAILURE (Status))
        {
            exit (-1);
        }
        exit (1);
    }

    /* Next parameter must be the input filename */

    if (!argv[AcpiGbl_Optind] &&
        !AcpiGbl_DisasmFlag)
    {
        printf ("Missing input filename\n");
        BadCommandLine = TRUE;
    }

    if (AslGbl_DoSignon)
    {
        printf (ACPI_COMMON_SIGNON (ASL_COMPILER_NAME));
        if (AslGbl_IgnoreErrors)
        {
            printf ("Ignoring all errors, forcing AML file generation\n\n");
        }
    }

    if (BadCommandLine)
    {
        printf ("Use -h option for help information\n");
        exit (1);
    }

    return (AcpiGbl_Optind);
}