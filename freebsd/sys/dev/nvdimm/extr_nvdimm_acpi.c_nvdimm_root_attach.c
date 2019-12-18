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
struct nvdimm_root_dev {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {int /*<<< orphan*/  Header; } ;
typedef  TYPE_1__ ACPI_TABLE_NFIT ;
typedef  int /*<<< orphan*/  ACPI_TABLE_HEADER ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SIG_NFIT ; 
 int /*<<< orphan*/  AcpiGetTable (int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  AcpiPutTable (int /*<<< orphan*/ *) ; 
 int ENXIO ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 struct nvdimm_root_dev* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int nvdimm_root_create_devs (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int nvdimm_root_create_spas (struct nvdimm_root_dev*,TYPE_1__*) ; 

__attribute__((used)) static int
nvdimm_root_attach(device_t dev)
{
	struct nvdimm_root_dev *root;
	ACPI_TABLE_NFIT *nfitbl;
	ACPI_STATUS status;
	int error;

	status = AcpiGetTable(ACPI_SIG_NFIT, 1, (ACPI_TABLE_HEADER **)&nfitbl);
	if (ACPI_FAILURE(status)) {
		device_printf(dev, "cannot get NFIT\n");
		return (ENXIO);
	}
	error = nvdimm_root_create_devs(dev, nfitbl);
	if (error != 0)
		return (error);
	error = bus_generic_attach(dev);
	if (error != 0)
		return (error);
	root = device_get_softc(dev);
	error = nvdimm_root_create_spas(root, nfitbl);
	AcpiPutTable(&nfitbl->Header);
	return (error);
}