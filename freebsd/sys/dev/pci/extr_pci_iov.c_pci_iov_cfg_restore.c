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
struct pcicfg_iov {int /*<<< orphan*/  iov_ctl; int /*<<< orphan*/  iov_num_vfs; int /*<<< orphan*/  iov_page_size; } ;
struct TYPE_2__ {struct pcicfg_iov* iov; } ;
struct pci_devinfo {TYPE_1__ cfg; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  IOV_WRITE (struct pci_devinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PCIR_SRIOV_CTL ; 
 int /*<<< orphan*/  PCIR_SRIOV_NUM_VFS ; 
 int /*<<< orphan*/  PCIR_SRIOV_PAGE_SIZE ; 

void
pci_iov_cfg_restore(device_t dev, struct pci_devinfo *dinfo)
{
	struct pcicfg_iov *iov;

	iov = dinfo->cfg.iov;

	IOV_WRITE(dinfo, PCIR_SRIOV_PAGE_SIZE, iov->iov_page_size, 4);
	IOV_WRITE(dinfo, PCIR_SRIOV_NUM_VFS, iov->iov_num_vfs, 2);
	IOV_WRITE(dinfo, PCIR_SRIOV_CTL, iov->iov_ctl, 2);
}