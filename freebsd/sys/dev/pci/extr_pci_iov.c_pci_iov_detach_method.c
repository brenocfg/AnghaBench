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
struct pcicfg_iov {scalar_t__ iov_num_vfs; int iov_flags; int /*<<< orphan*/  iov_schema; int /*<<< orphan*/ * iov_cdev; } ;
struct TYPE_2__ {struct pcicfg_iov* iov; } ;
struct pci_devinfo {TYPE_1__ cfg; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  Giant ; 
 int IOV_BUSY ; 
 int /*<<< orphan*/  M_SRIOV ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ *) ; 
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct pcicfg_iov*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ ) ; 

int
pci_iov_detach_method(device_t bus, device_t dev)
{
	struct pci_devinfo *dinfo;
	struct pcicfg_iov *iov;

	mtx_lock(&Giant);
	dinfo = device_get_ivars(dev);
	iov = dinfo->cfg.iov;

	if (iov == NULL) {
		mtx_unlock(&Giant);
		return (0);
	}

	if (iov->iov_num_vfs != 0 || iov->iov_flags & IOV_BUSY) {
		mtx_unlock(&Giant);
		return (EBUSY);
	}

	dinfo->cfg.iov = NULL;

	if (iov->iov_cdev) {
		destroy_dev(iov->iov_cdev);
		iov->iov_cdev = NULL;
	}
	nvlist_destroy(iov->iov_schema);

	free(iov, M_SRIOV);
	mtx_unlock(&Giant);

	return (0);
}