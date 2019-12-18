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
struct acpi_throttle_softc {int dummy; } ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_QUIRK_NO_THROTTLE ; 
 int /*<<< orphan*/  PCI_DEVICE_82371AB_3 ; 
#define  PCI_REVISION_A_STEP 129 
#define  PCI_REVISION_B_STEP 128 
 int /*<<< orphan*/  PCI_VENDOR_INTEL ; 
 scalar_t__ pci_find_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pci_get_revid (scalar_t__) ; 
 int /*<<< orphan*/  thr_quirks ; 

__attribute__((used)) static void
acpi_throttle_quirks(struct acpi_throttle_softc *sc)
{
#ifdef __i386__
	device_t acpi_dev;

	/* Look for various quirks of the PIIX4 part. */
	acpi_dev = pci_find_device(PCI_VENDOR_INTEL, PCI_DEVICE_82371AB_3);
	if (acpi_dev) {
		switch (pci_get_revid(acpi_dev)) {
		/*
		 * Disable throttling control on PIIX4 A and B-step.
		 * See specification changes #13 ("Manual Throttle Duty Cycle")
		 * and #14 ("Enabling and Disabling Manual Throttle"), plus
		 * erratum #5 ("STPCLK# Deassertion Time") from the January
		 * 2002 PIIX4 specification update.  Note that few (if any)
		 * mobile systems ever used this part.
		 */
		case PCI_REVISION_A_STEP:
		case PCI_REVISION_B_STEP:
			thr_quirks |= CPU_QUIRK_NO_THROTTLE;
			break;
		default:
			break;
		}
	}
#endif
}