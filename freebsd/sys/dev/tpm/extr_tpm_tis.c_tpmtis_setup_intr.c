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
struct tpm_sc {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 int ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiWalkResources (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,void*) ; 
 int RD4 (struct tpm_sc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TPM_INT_ENABLE ; 
 int TPM_INT_ENABLE_CMD_RDY ; 
 int TPM_INT_ENABLE_DATA_AVAIL ; 
 int TPM_INT_ENABLE_GLOBAL_ENABLE ; 
 int TPM_INT_ENABLE_LOC_CHANGE ; 
 int TPM_INT_ENABLE_STS_VALID ; 
 int /*<<< orphan*/  WR4 (struct tpm_sc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpmtis_get_SIRQ_channel ; 
 int /*<<< orphan*/  tpmtis_relinquish_locality (struct tpm_sc*) ; 
 int /*<<< orphan*/  tpmtis_request_locality (struct tpm_sc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
tpmtis_setup_intr(struct tpm_sc *sc)
{
	ACPI_STATUS status;
	ACPI_HANDLE handle;
	uint32_t irq_mask;

	handle = acpi_get_handle(sc->dev);

	if(!tpmtis_request_locality(sc, 0))
		return (false);

	irq_mask = RD4(sc, TPM_INT_ENABLE);
	irq_mask |= TPM_INT_ENABLE_GLOBAL_ENABLE |
	    TPM_INT_ENABLE_DATA_AVAIL |
	    TPM_INT_ENABLE_LOC_CHANGE |
	    TPM_INT_ENABLE_CMD_RDY |
	    TPM_INT_ENABLE_STS_VALID;
	WR4(sc, TPM_INT_ENABLE, irq_mask);

	status = AcpiWalkResources(handle, "_CRS",
	    tpmtis_get_SIRQ_channel, (void *)sc);

	tpmtis_relinquish_locality(sc);

	return (ACPI_SUCCESS(status));
}