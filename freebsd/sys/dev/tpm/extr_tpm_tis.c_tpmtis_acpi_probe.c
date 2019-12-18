#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ StartMethod; } ;
typedef  TYPE_1__ ACPI_TABLE_TPM23 ;
typedef  int /*<<< orphan*/  ACPI_TABLE_HEADER ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int ACPI_ID_PROBE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ACPI_SIG_TPM2 ; 
 int /*<<< orphan*/  AcpiGetTable (int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int ENXIO ; 
 scalar_t__ TPM2_START_METHOD_TIS ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tpmtis_ids ; 

__attribute__((used)) static int
tpmtis_acpi_probe(device_t dev)
{
	int err;
	ACPI_TABLE_TPM23 *tbl;
	ACPI_STATUS status;

	err = ACPI_ID_PROBE(device_get_parent(dev), dev, tpmtis_ids, NULL);
	if (err > 0)
		return (err);
	/*Find TPM2 Header*/
	status = AcpiGetTable(ACPI_SIG_TPM2, 1, (ACPI_TABLE_HEADER **) &tbl);
	if(ACPI_FAILURE(status) ||
	   tbl->StartMethod != TPM2_START_METHOD_TIS)
	    err = ENXIO;

	device_set_desc(dev, "Trusted Platform Module 2.0, FIFO mode");
	return (err);
}