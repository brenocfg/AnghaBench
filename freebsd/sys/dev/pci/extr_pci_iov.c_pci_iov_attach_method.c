#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct pcicfg_iov {int iov_pos; TYPE_2__* iov_cdev; int /*<<< orphan*/ * iov_schema; } ;
struct TYPE_3__ {struct pcicfg_iov* iov; } ;
struct pci_devinfo {TYPE_1__ cfg; } ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {struct pci_devinfo* si_drv1; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  M_SRIOV ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PCIZ_SRIOV ; 
 int PCI_EXTCAP_VER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UID_ROOT ; 
 scalar_t__ bootverbose ; 
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free (struct pcicfg_iov*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iov_cdevsw ; 
 TYPE_2__* make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,char const*) ; 
 struct pcicfg_iov* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ *) ; 
 int pci_find_extcap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * pci_iov_build_schema (int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int pci_iov_validate_schema (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_read_config (int /*<<< orphan*/ ,int,int) ; 

int
pci_iov_attach_method(device_t bus, device_t dev, nvlist_t *pf_schema,
    nvlist_t *vf_schema, const char *name)
{
	device_t pcib;
	struct pci_devinfo *dinfo;
	struct pcicfg_iov *iov;
	nvlist_t *schema;
	uint32_t version;
	int error;
	int iov_pos;

	dinfo = device_get_ivars(dev);
	pcib = device_get_parent(bus);
	schema = NULL;
	
	error = pci_find_extcap(dev, PCIZ_SRIOV, &iov_pos);

	if (error != 0)
		return (error);

	version = pci_read_config(dev, iov_pos, 4); 
	if (PCI_EXTCAP_VER(version) != 1) {
		if (bootverbose)
			device_printf(dev, 
			    "Unsupported version of SR-IOV (%d) detected\n",
			    PCI_EXTCAP_VER(version));

		return (ENXIO);
	}

	iov = malloc(sizeof(*dinfo->cfg.iov), M_SRIOV, M_WAITOK | M_ZERO);

	mtx_lock(&Giant);
	if (dinfo->cfg.iov != NULL) {
		error = EBUSY;
		goto cleanup;
	}
	iov->iov_pos = iov_pos;

	schema = pci_iov_build_schema(&pf_schema, &vf_schema);
	if (schema == NULL) {
		error = ENOMEM;
		goto cleanup;
	}

	error = pci_iov_validate_schema(schema);
	if (error != 0)
		goto cleanup;
	iov->iov_schema = schema;

	iov->iov_cdev = make_dev(&iov_cdevsw, device_get_unit(dev),
	    UID_ROOT, GID_WHEEL, 0600, "iov/%s", name);

	if (iov->iov_cdev == NULL) {
		error = ENOMEM;
		goto cleanup;
	}
	
	dinfo->cfg.iov = iov;
	iov->iov_cdev->si_drv1 = dinfo;
	mtx_unlock(&Giant);

	return (0);

cleanup:
	nvlist_destroy(schema);
	nvlist_destroy(pf_schema);
	nvlist_destroy(vf_schema);
	free(iov, M_SRIOV);
	mtx_unlock(&Giant);
	return (error);
}