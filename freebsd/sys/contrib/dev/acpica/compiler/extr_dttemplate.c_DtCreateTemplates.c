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
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 char* ACPI_SIG_DSDT ; 
 int /*<<< orphan*/  AE_LIMIT ; 
 int /*<<< orphan*/  AE_OK ; 
 int AcpiGbl_Optind ; 
 int /*<<< orphan*/  AcpiTerminate () ; 
 int /*<<< orphan*/  AcpiUtStrupr (char*) ; 
 int /*<<< orphan*/  AdInitialize () ; 
 int /*<<< orphan*/  AslInitializeGlobals () ; 
 int /*<<< orphan*/  DtCreateAllTemplates () ; 
 int /*<<< orphan*/  DtCreateOneTemplateFile (char*,unsigned long) ; 
 int /*<<< orphan*/  UtDeleteLocalCaches () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 unsigned long strtoul (char*,char**,int /*<<< orphan*/ ) ; 

ACPI_STATUS
DtCreateTemplates (
    char                    **argv)
{
    char                    *Signature;
    char                    *End;
    unsigned long           TableCount;
    ACPI_STATUS             Status = AE_OK;


    AslInitializeGlobals ();

    Status = AdInitialize ();
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

    /*
     * Special cases for DSDT, ALL, and '*'
     */

    /* Default (no signature option) is DSDT */

    if (AcpiGbl_Optind < 3)
    {
        Status = DtCreateOneTemplateFile (ACPI_SIG_DSDT, 0);
        goto Exit;
    }

    AcpiGbl_Optind--;
    Signature = argv[AcpiGbl_Optind];
    AcpiUtStrupr (Signature);

    /*
     * Multiple SSDT support (-T <ssdt count>)
     */
    TableCount = strtoul (Signature, &End, 0);
    if (Signature != End)
    {
        /* The count is used for table ID and method name - max is 254(+1) */

        if (TableCount > 254)
        {
            fprintf (stderr, "%u SSDTs requested, maximum is 254\n",
                (unsigned int) TableCount);

            Status = AE_LIMIT;
            goto Exit;
        }

        Status = DtCreateOneTemplateFile (ACPI_SIG_DSDT, TableCount);
        goto Exit;
    }

    if (!strcmp (Signature, "ALL"))
    {
        /* Create all available/known templates */

        Status = DtCreateAllTemplates ();
        goto Exit;
    }

    /*
     * Normal case: Create template for each signature
     */
    while (argv[AcpiGbl_Optind])
    {
        Signature = argv[AcpiGbl_Optind];
        AcpiUtStrupr (Signature);

        Status = DtCreateOneTemplateFile (Signature, 0);
        if (ACPI_FAILURE (Status))
        {
            goto Exit;
        }

        AcpiGbl_Optind++;
    }


Exit:
    /* Shutdown ACPICA subsystem */

    (void) AcpiTerminate ();
    UtDeleteLocalCaches ();
    return (Status);
}