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

/* Variables and functions */
 int /*<<< orphan*/  ACPI_OPTION_ERROR (char*,int) ; 
 int ACPI_OPT_END ; 
 char* AcpiGbl_Optarg ; 
 int AcpiGbl_Optind ; 
 char AcpiGbl_SubOptChar ; 
 int CurrentCharPtr ; 
 char* strchr (char*,int) ; 
 scalar_t__ strcmp (char*,char*) ; 

int
AcpiGetopt(
    int                     argc,
    char                    **argv,
    char                    *opts)
{
    int                     CurrentChar;
    char                    *OptsPtr;


    if (CurrentCharPtr == 1)
    {
        if (AcpiGbl_Optind >= argc ||
            argv[AcpiGbl_Optind][0] != '-' ||
            argv[AcpiGbl_Optind][1] == '\0')
        {
            return (ACPI_OPT_END);
        }
        else if (strcmp (argv[AcpiGbl_Optind], "--") == 0)
        {
            AcpiGbl_Optind++;
            return (ACPI_OPT_END);
        }
    }

    /* Get the option */

    CurrentChar = argv[AcpiGbl_Optind][CurrentCharPtr];

    /* Make sure that the option is legal */

    if (CurrentChar == ':' ||
       (OptsPtr = strchr (opts, CurrentChar)) == NULL)
    {
        ACPI_OPTION_ERROR ("Illegal option: -", CurrentChar);

        if (argv[AcpiGbl_Optind][++CurrentCharPtr] == '\0')
        {
            AcpiGbl_Optind++;
            CurrentCharPtr = 1;
        }

        return ('?');
    }

    /* Option requires an argument? */

    if (*++OptsPtr == ':')
    {
        if (argv[AcpiGbl_Optind][(int) (CurrentCharPtr+1)] != '\0')
        {
            AcpiGbl_Optarg = &argv[AcpiGbl_Optind++][(int) (CurrentCharPtr+1)];
        }
        else if (++AcpiGbl_Optind >= argc)
        {
            ACPI_OPTION_ERROR (
                "Option requires an argument: -", CurrentChar);

            CurrentCharPtr = 1;
            return ('?');
        }
        else
        {
            AcpiGbl_Optarg = argv[AcpiGbl_Optind++];
        }

        CurrentCharPtr = 1;
    }

    /* Option has an optional argument? */

    else if (*OptsPtr == '+')
    {
        if (argv[AcpiGbl_Optind][(int) (CurrentCharPtr+1)] != '\0')
        {
            AcpiGbl_Optarg = &argv[AcpiGbl_Optind++][(int) (CurrentCharPtr+1)];
        }
        else if (++AcpiGbl_Optind >= argc)
        {
            AcpiGbl_Optarg = NULL;
        }
        else
        {
            AcpiGbl_Optarg = argv[AcpiGbl_Optind++];
        }

        CurrentCharPtr = 1;
    }

    /* Option has optional single-char arguments? */

    else if (*OptsPtr == '^')
    {
        if (argv[AcpiGbl_Optind][(int) (CurrentCharPtr+1)] != '\0')
        {
            AcpiGbl_Optarg = &argv[AcpiGbl_Optind][(int) (CurrentCharPtr+1)];
        }
        else
        {
            AcpiGbl_Optarg = "^";
        }

        AcpiGbl_SubOptChar = AcpiGbl_Optarg[0];
        AcpiGbl_Optind++;
        CurrentCharPtr = 1;
    }

    /* Option has a required single-char argument? */

    else if (*OptsPtr == '|')
    {
        if (argv[AcpiGbl_Optind][(int) (CurrentCharPtr+1)] != '\0')
        {
            AcpiGbl_Optarg = &argv[AcpiGbl_Optind][(int) (CurrentCharPtr+1)];
        }
        else
        {
            ACPI_OPTION_ERROR (
                "Option requires a single-character suboption: -",
                CurrentChar);

            CurrentCharPtr = 1;
            return ('?');
        }

        AcpiGbl_SubOptChar = AcpiGbl_Optarg[0];
        AcpiGbl_Optind++;
        CurrentCharPtr = 1;
    }

    /* Option with no arguments */

    else
    {
        if (argv[AcpiGbl_Optind][++CurrentCharPtr] == '\0')
        {
            CurrentCharPtr = 1;
            AcpiGbl_Optind++;
        }

        AcpiGbl_Optarg = NULL;
    }

    return (CurrentChar);
}