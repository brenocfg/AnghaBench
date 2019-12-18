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
struct nvdimm_dev {int /*<<< orphan*/  nv_flush_addr_cnt; int /*<<< orphan*/  nv_flush_addr; int /*<<< orphan*/  nv_handle; int /*<<< orphan*/  nv_dev; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {int /*<<< orphan*/  Header; } ;
typedef  TYPE_1__ ACPI_TABLE_NFIT ;
typedef  int /*<<< orphan*/  ACPI_TABLE_HEADER ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/ * ACPI_HANDLE ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SIG_NFIT ; 
 int /*<<< orphan*/  AcpiGetTable (int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  AcpiPutTable (int /*<<< orphan*/ *) ; 
 int ENXIO ; 
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_nfit_get_flush_addrs (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bootverbose ; 
 struct nvdimm_dev* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * nvdimm_root_get_acpi_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvdimm_root_get_device_handle (int /*<<< orphan*/ ) ; 
 int read_label_area_size (struct nvdimm_dev*) ; 
 int /*<<< orphan*/  read_labels (struct nvdimm_dev*) ; 

__attribute__((used)) static int
nvdimm_attach(device_t dev)
{
	struct nvdimm_dev *nv;
	ACPI_TABLE_NFIT *nfitbl;
	ACPI_HANDLE handle;
	ACPI_STATUS status;
	int error;

	nv = device_get_softc(dev);
	handle = nvdimm_root_get_acpi_handle(dev);
	MPASS(handle != NULL);
	nv->nv_dev = dev;
	nv->nv_handle = nvdimm_root_get_device_handle(dev);

	status = AcpiGetTable(ACPI_SIG_NFIT, 1, (ACPI_TABLE_HEADER **)&nfitbl);
	if (ACPI_FAILURE(status)) {
		if (bootverbose)
			device_printf(dev, "cannot get NFIT\n");
		return (ENXIO);
	}
	acpi_nfit_get_flush_addrs(nfitbl, nv->nv_handle, &nv->nv_flush_addr,
	    &nv->nv_flush_addr_cnt);
	AcpiPutTable(&nfitbl->Header);
	error = read_label_area_size(nv);
	if (error == 0) {
		/*
		 * Ignoring errors reading labels. Not all NVDIMMs
		 * support labels and namespaces.
		 */
		read_labels(nv);
	}
	return (0);
}