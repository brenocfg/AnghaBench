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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/ * device_t ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BITREG_BUS_MASTER_RLD ; 
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiReadBitRegister (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  AcpiWriteBitRegister (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPU_QUIRK_NO_C3 ; 
 int /*<<< orphan*/  PCI_DEVICE_82371AB_3 ; 
#define  PCI_REVISION_4E 131 
#define  PCI_REVISION_4M 130 
#define  PCI_REVISION_A_STEP 129 
#define  PCI_REVISION_B_STEP 128 
 int /*<<< orphan*/  PCI_VENDOR_INTEL ; 
 int /*<<< orphan*/  PIIX4_DEVACTB_REG ; 
 int PIIX4_STOP_BREAK_MASK ; 
 int /*<<< orphan*/  cpu_quirks ; 
 int /*<<< orphan*/ * pci_find_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pci_get_revid (int /*<<< orphan*/ *) ; 
 int pci_read_config (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
acpi_cpu_quirks_piix4(void)
{
#ifdef __i386__
    device_t acpi_dev;
    uint32_t val;
    ACPI_STATUS status;

    acpi_dev = pci_find_device(PCI_VENDOR_INTEL, PCI_DEVICE_82371AB_3);
    if (acpi_dev != NULL) {
	switch (pci_get_revid(acpi_dev)) {
	/*
	 * Disable C3 support for all PIIX4 chipsets.  Some of these parts
	 * do not report the BMIDE status to the BM status register and
	 * others have a livelock bug if Type-F DMA is enabled.  Linux
	 * works around the BMIDE bug by reading the BM status directly
	 * but we take the simpler approach of disabling C3 for these
	 * parts.
	 *
	 * See erratum #18 ("C3 Power State/BMIDE and Type-F DMA
	 * Livelock") from the January 2002 PIIX4 specification update.
	 * Applies to all PIIX4 models.
	 *
	 * Also, make sure that all interrupts cause a "Stop Break"
	 * event to exit from C2 state.
	 * Also, BRLD_EN_BM (ACPI_BITREG_BUS_MASTER_RLD in ACPI-speak)
	 * should be set to zero, otherwise it causes C2 to short-sleep.
	 * PIIX4 doesn't properly support C3 and bus master activity
	 * need not break out of C2.
	 */
	case PCI_REVISION_A_STEP:
	case PCI_REVISION_B_STEP:
	case PCI_REVISION_4E:
	case PCI_REVISION_4M:
	    cpu_quirks |= CPU_QUIRK_NO_C3;
	    ACPI_DEBUG_PRINT((ACPI_DB_INFO,
		"acpi_cpu: working around PIIX4 bug, disabling C3\n"));

	    val = pci_read_config(acpi_dev, PIIX4_DEVACTB_REG, 4);
	    if ((val & PIIX4_STOP_BREAK_MASK) != PIIX4_STOP_BREAK_MASK) {
		ACPI_DEBUG_PRINT((ACPI_DB_INFO,
		    "acpi_cpu: PIIX4: enabling IRQs to generate Stop Break\n"));
	    	val |= PIIX4_STOP_BREAK_MASK;
		pci_write_config(acpi_dev, PIIX4_DEVACTB_REG, val, 4);
	    }
	    status = AcpiReadBitRegister(ACPI_BITREG_BUS_MASTER_RLD, &val);
	    if (ACPI_SUCCESS(status) && val != 0) {
		ACPI_DEBUG_PRINT((ACPI_DB_INFO,
		    "acpi_cpu: PIIX4: reset BRLD_EN_BM\n"));
		AcpiWriteBitRegister(ACPI_BITREG_BUS_MASTER_RLD, 0);
	    }
	    break;
	default:
	    break;
	}
    }
#endif
}