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
typedef  int /*<<< orphan*/  xsdt ;
struct acpi_q_rule {char* sig; } ;
struct acpi_q_entry {int quirks; struct acpi_q_rule* match; } ;
typedef  int /*<<< orphan*/  fadt ;
typedef  int /*<<< orphan*/  dsdt ;
typedef  int /*<<< orphan*/  ACPI_TABLE_HEADER ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_NAMESEG_SIZE ; 
 char* ACPI_SIG_DSDT ; 
 char* ACPI_SIG_FADT ; 
 char* ACPI_SIG_XSDT ; 
 int /*<<< orphan*/  AcpiGetTableHeader (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int FALSE ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int TRUE ; 
 int /*<<< orphan*/  acpi_machdep_quirks (int*) ; 
 struct acpi_q_entry* acpi_quirks_table ; 
 int aq_match_header (int /*<<< orphan*/ *,struct acpi_q_rule const*) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int /*<<< orphan*/ ) ; 

int
acpi_table_quirks(int *quirks)
{
    const struct acpi_q_entry *entry;
    const struct acpi_q_rule *match;
    ACPI_TABLE_HEADER fadt, dsdt, xsdt, *hdr;
    int done;

    /* First, allow the machdep system to set its idea of quirks. */
    KASSERT(quirks != NULL, ("acpi quirks ptr is NULL"));
    acpi_machdep_quirks(quirks);

    if (ACPI_FAILURE(AcpiGetTableHeader(ACPI_SIG_FADT, 0, &fadt)))
	bzero(&fadt, sizeof(fadt));
    if (ACPI_FAILURE(AcpiGetTableHeader(ACPI_SIG_DSDT, 0, &dsdt)))
	bzero(&dsdt, sizeof(dsdt));
    if (ACPI_FAILURE(AcpiGetTableHeader(ACPI_SIG_XSDT, 0, &xsdt)))
	bzero(&xsdt, sizeof(xsdt));

    /* Then, override the quirks with any matched from table signatures. */
    for (entry = acpi_quirks_table; entry->match; entry++) {
	done = TRUE;
	for (match = entry->match; match->sig[0] != '\0'; match++) {
	    if (!strncmp(match->sig, "FADT", ACPI_NAMESEG_SIZE))
		hdr = &fadt;
	    else if (!strncmp(match->sig, ACPI_SIG_DSDT, ACPI_NAMESEG_SIZE))
		hdr = &dsdt;
	    else if (!strncmp(match->sig, ACPI_SIG_XSDT, ACPI_NAMESEG_SIZE))
		hdr = &xsdt;
	    else
		panic("invalid quirk header\n");

	    /* If we don't match any, skip to the next entry. */
	    if (aq_match_header(hdr, match) == FALSE) {
		done = FALSE;
		break;
	    }
	}

	/* If all entries matched, update the quirks and return. */
	if (done) {
	    *quirks = entry->quirks;
	    break;
	}
    }

    return (0);
}