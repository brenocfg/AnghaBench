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
typedef  int /*<<< orphan*/  nfit_handle_t ;
typedef  int /*<<< orphan*/ * device_t ;
typedef  int /*<<< orphan*/  ACPI_TABLE_NFIT ;
typedef  int /*<<< orphan*/ * ACPI_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/ * BUS_ADD_CHILD (int /*<<< orphan*/ *,int,char*,int) ; 
 int ENXIO ; 
 int /*<<< orphan*/  M_NVDIMM_ACPI ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NVDIMM_ROOT_IVAR_MAX ; 
 int /*<<< orphan*/ * acpi_get_handle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_nfit_get_dimm_ids (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,uintptr_t*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_dimm_acpi_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 uintptr_t* mallocarray (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvdimm_root_set_acpi_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvdimm_root_set_device_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nvdimm_root_create_devs(device_t dev, ACPI_TABLE_NFIT *nfitbl)
{
	ACPI_HANDLE root_handle, dimm_handle;
	device_t child;
	nfit_handle_t *dimm_ids, *dimm;
	uintptr_t *ivars;
	int num_dimm_ids;

	root_handle = acpi_get_handle(dev);
	acpi_nfit_get_dimm_ids(nfitbl, &dimm_ids, &num_dimm_ids);
	for (dimm = dimm_ids; dimm < dimm_ids + num_dimm_ids; dimm++) {
		dimm_handle = get_dimm_acpi_handle(root_handle, *dimm);
		if (dimm_handle == NULL)
			continue;

		child = BUS_ADD_CHILD(dev, 100, "nvdimm", -1);
		if (child == NULL) {
			device_printf(dev, "failed to create nvdimm\n");
			return (ENXIO);
		}
		ivars = mallocarray(NVDIMM_ROOT_IVAR_MAX, sizeof(uintptr_t),
		    M_NVDIMM_ACPI, M_ZERO | M_WAITOK);
		device_set_ivars(child, ivars);
		nvdimm_root_set_acpi_handle(child, dimm_handle);
		nvdimm_root_set_device_handle(child, *dimm);
	}
	free(dimm_ids, M_NVDIMM_ACPI);
	return (0);
}