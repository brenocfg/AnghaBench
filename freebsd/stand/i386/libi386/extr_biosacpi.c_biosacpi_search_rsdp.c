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
typedef  scalar_t__ uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  Signature; } ;
typedef  TYPE_1__ ACPI_TABLE_RSDP ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SIG_RSDP ; 
 scalar_t__ PTOV (char*) ; 
 int RSDP_CHECKSUM_LENGTH ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ACPI_TABLE_RSDP *
biosacpi_search_rsdp(char *base, int length)
{
    ACPI_TABLE_RSDP	*rsdp;
    uint8_t		*cp, sum;
    int			ofs, idx;

    /* search on 16-byte boundaries */
    for (ofs = 0; ofs < length; ofs += 16) {
	rsdp = (ACPI_TABLE_RSDP *)PTOV(base + ofs);

	/* compare signature, validate checksum */
	if (!strncmp(rsdp->Signature, ACPI_SIG_RSDP, strlen(ACPI_SIG_RSDP))) {
	    cp = (uint8_t *)rsdp;
	    sum = 0;
	    for (idx = 0; idx < RSDP_CHECKSUM_LENGTH; idx++)
		sum += *(cp + idx);
	    if (sum != 0)
		continue;
	    return(rsdp);
	}
    }
    return(NULL);
}