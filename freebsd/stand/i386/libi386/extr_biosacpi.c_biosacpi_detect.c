#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int Revision; int RsdtPhysicalAddress; int XsdtPhysicalAddress; int Length; int /*<<< orphan*/  OemId; } ;
typedef  TYPE_1__ ACPI_TABLE_RSDP ;

/* Variables and functions */
 int VTOP (TYPE_1__*) ; 
 TYPE_1__* biosacpi_find_rsdp () ; 
 int /*<<< orphan*/  setenv (char*,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 

void
biosacpi_detect(void)
{
    ACPI_TABLE_RSDP	*rsdp;
    char		buf[24];
    int			revision;

    /* locate and validate the RSDP */
    if ((rsdp = biosacpi_find_rsdp()) == NULL)
	return;

    /*
     * Report the RSDP to the kernel. While this can be found with
     * a BIOS boot, the RSDP may be elsewhere when booted from UEFI.
     * The old code used the 'hints' method to communite this to
     * the kernel. However, while convenient, the 'hints' method
     * is fragile and does not work when static hints are compiled
     * into the kernel. Instead, move to setting different tunables
     * that start with acpi. The old 'hints' can be removed before
     * we branch for FreeBSD 12.
     */
    sprintf(buf, "0x%08x", VTOP(rsdp));
    setenv("hint.acpi.0.rsdp", buf, 1);
    setenv("acpi.rsdp", buf, 1);
    revision = rsdp->Revision;
    if (revision == 0)
	revision = 1;
    sprintf(buf, "%d", revision);
    setenv("hint.acpi.0.revision", buf, 1);
    setenv("acpi.revision", buf, 1);
    strncpy(buf, rsdp->OemId, sizeof(rsdp->OemId));
    buf[sizeof(rsdp->OemId)] = '\0';
    setenv("hint.acpi.0.oem", buf, 1);
    setenv("acpi.oem", buf, 1);
    sprintf(buf, "0x%08x", rsdp->RsdtPhysicalAddress);
    setenv("hint.acpi.0.rsdt", buf, 1);
    setenv("acpi.rsdt", buf, 1);
    if (revision >= 2) {
	/* XXX extended checksum? */
	sprintf(buf, "0x%016llx", rsdp->XsdtPhysicalAddress);
	setenv("hint.acpi.0.xsdt", buf, 1);
	setenv("acpi.xsdt", buf, 1);
	sprintf(buf, "%d", rsdp->Length);
	setenv("hint.acpi.0.xsdt_length", buf, 1);
	setenv("acpi.xsdt_length", buf, 1);
    }
}