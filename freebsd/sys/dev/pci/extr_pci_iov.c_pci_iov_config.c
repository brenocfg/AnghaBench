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
typedef  int uint16_t ;
struct pcicfg_iov {int iov_flags; int iov_num_vfs; int /*<<< orphan*/  rman; TYPE_2__* iov_bar; scalar_t__ iov_pos; } ;
struct pci_iov_arg {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; struct pcicfg_iov* iov; } ;
struct pci_devinfo {TYPE_1__ cfg; } ;
struct cdev {struct pci_devinfo* si_drv1; } ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {int /*<<< orphan*/ * res; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOSPC ; 
 int /*<<< orphan*/  Giant ; 
 int IOV_BUSY ; 
 int IOV_READ (struct pci_devinfo*,int /*<<< orphan*/ ,int) ; 
 int IOV_RMAN_INITED ; 
 int /*<<< orphan*/  IOV_WRITE (struct pci_devinfo*,int /*<<< orphan*/ ,int,int) ; 
 int PCIM_SRIOV_VF_EN ; 
 int PCIM_SRIOV_VF_MSE ; 
 int PCIR_MAX_BAR_0 ; 
 scalar_t__ PCIR_SRIOV_BAR (int) ; 
 int /*<<< orphan*/  PCIR_SRIOV_CTL ; 
 int /*<<< orphan*/  PCIR_SRIOV_NUM_VFS ; 
 int /*<<< orphan*/  PCIR_SRIOV_TOTAL_VFS ; 
 int /*<<< orphan*/  PCIR_SRIOV_VF_OFF ; 
 int /*<<< orphan*/  PCIR_SRIOV_VF_STRIDE ; 
 int /*<<< orphan*/  PCI_IOV_UNINIT (int /*<<< orphan*/ ) ; 
 scalar_t__ PCI_RID2BUS (int) ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pause (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_delete_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ pci_get_bus (int /*<<< orphan*/ ) ; 
 int pci_get_rid (int /*<<< orphan*/ ) ; 
 int pci_iov_config_get_num_vfs (int /*<<< orphan*/ *) ; 
 int pci_iov_config_page_size (struct pci_devinfo*) ; 
 int /*<<< orphan*/  pci_iov_enumerate_vfs (struct pci_devinfo*,int /*<<< orphan*/ *,int,int) ; 
 int pci_iov_init (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int pci_iov_init_rman (int /*<<< orphan*/ ,struct pcicfg_iov*) ; 
 int pci_iov_parse_config (struct pcicfg_iov*,struct pci_iov_arg*,int /*<<< orphan*/ **) ; 
 int pci_iov_set_ari (int /*<<< orphan*/ ) ; 
 int pci_iov_setup_bars (struct pci_devinfo*) ; 
 int /*<<< orphan*/  pci_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  roundup (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
pci_iov_config(struct cdev *cdev, struct pci_iov_arg *arg)
{
	device_t bus, dev;
	struct pci_devinfo *dinfo;
	struct pcicfg_iov *iov;
	nvlist_t *config;
	int i, error;
	uint16_t rid_off, rid_stride;
	uint16_t first_rid, last_rid;
	uint16_t iov_ctl;
	uint16_t num_vfs, total_vfs;
	int iov_inited;

	mtx_lock(&Giant);
	dinfo = cdev->si_drv1;
	iov = dinfo->cfg.iov;
	dev = dinfo->cfg.dev;
	bus = device_get_parent(dev);
	iov_inited = 0;
	config = NULL;

	if ((iov->iov_flags & IOV_BUSY) || iov->iov_num_vfs != 0) {
		mtx_unlock(&Giant);
		return (EBUSY);
	}
	iov->iov_flags |= IOV_BUSY;

	error = pci_iov_parse_config(iov, arg, &config);
	if (error != 0)
		goto out;

	num_vfs = pci_iov_config_get_num_vfs(config);
	total_vfs = IOV_READ(dinfo, PCIR_SRIOV_TOTAL_VFS, 2);
	if (num_vfs > total_vfs) {
		error = EINVAL;
		goto out;
	}

	error = pci_iov_config_page_size(dinfo);
	if (error != 0)
		goto out;

	error = pci_iov_set_ari(bus);
	if (error != 0)
		goto out;

	error = pci_iov_init(dev, num_vfs, config);
	if (error != 0)
		goto out;
	iov_inited = 1;

	IOV_WRITE(dinfo, PCIR_SRIOV_NUM_VFS, num_vfs, 2);

	rid_off = IOV_READ(dinfo, PCIR_SRIOV_VF_OFF, 2);
	rid_stride = IOV_READ(dinfo, PCIR_SRIOV_VF_STRIDE, 2);

	first_rid = pci_get_rid(dev) + rid_off;
	last_rid = first_rid + (num_vfs - 1) * rid_stride;

	/* We don't yet support allocating extra bus numbers for VFs. */
	if (pci_get_bus(dev) != PCI_RID2BUS(last_rid)) {
		error = ENOSPC;
		goto out;
	}

	iov_ctl = IOV_READ(dinfo, PCIR_SRIOV_CTL, 2);
	iov_ctl &= ~(PCIM_SRIOV_VF_EN | PCIM_SRIOV_VF_MSE);
	IOV_WRITE(dinfo, PCIR_SRIOV_CTL, iov_ctl, 2);

	error = pci_iov_init_rman(dev, iov);
	if (error != 0)
		goto out;

	iov->iov_num_vfs = num_vfs;

	error = pci_iov_setup_bars(dinfo);
	if (error != 0)
		goto out;

	iov_ctl = IOV_READ(dinfo, PCIR_SRIOV_CTL, 2);
	iov_ctl |= PCIM_SRIOV_VF_EN | PCIM_SRIOV_VF_MSE;
	IOV_WRITE(dinfo, PCIR_SRIOV_CTL, iov_ctl, 2);

	/* Per specification, we must wait 100ms before accessing VFs. */
	pause("iov", roundup(hz, 10));
	pci_iov_enumerate_vfs(dinfo, config, first_rid, rid_stride);

	nvlist_destroy(config);
	iov->iov_flags &= ~IOV_BUSY;
	mtx_unlock(&Giant);

	return (0);
out:
	if (iov_inited)
		PCI_IOV_UNINIT(dev);

	for (i = 0; i <= PCIR_MAX_BAR_0; i++) {
		if (iov->iov_bar[i].res != NULL) {
			pci_release_resource(bus, dev, SYS_RES_MEMORY,
			    iov->iov_pos + PCIR_SRIOV_BAR(i),
			    iov->iov_bar[i].res);
			pci_delete_resource(bus, dev, SYS_RES_MEMORY,
			    iov->iov_pos + PCIR_SRIOV_BAR(i));
			iov->iov_bar[i].res = NULL;
		}
	}

	if (iov->iov_flags & IOV_RMAN_INITED) {
		rman_fini(&iov->rman);
		iov->iov_flags &= ~IOV_RMAN_INITED;
	}

	nvlist_destroy(config);
	iov->iov_num_vfs = 0;
	iov->iov_flags &= ~IOV_BUSY;
	mtx_unlock(&Giant);
	return (error);
}