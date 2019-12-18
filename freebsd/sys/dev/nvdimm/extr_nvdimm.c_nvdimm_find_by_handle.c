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
struct nvdimm_dev {int dummy; } ;
typedef  scalar_t__ nfit_handle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_TEMP ; 
 int devclass_get_devices (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 
 struct nvdimm_dev* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvdimm_devclass ; 
 scalar_t__ nvdimm_root_get_device_handle (int /*<<< orphan*/ ) ; 

struct nvdimm_dev *
nvdimm_find_by_handle(nfit_handle_t nv_handle)
{
	struct nvdimm_dev *res;
	device_t *dimms;
	int i, error, num_dimms;

	res = NULL;
	error = devclass_get_devices(nvdimm_devclass, &dimms, &num_dimms);
	if (error != 0)
		return (NULL);
	for (i = 0; i < num_dimms; i++) {
		if (nvdimm_root_get_device_handle(dimms[i]) == nv_handle) {
			res = device_get_softc(dimms[i]);
			break;
		}
	}
	free(dimms, M_TEMP);
	return (res);
}