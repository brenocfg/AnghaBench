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
struct pcicfg_iov {void* iov_ctl; void* iov_page_size; } ;
struct TYPE_2__ {struct pcicfg_iov* iov; } ;
struct pci_devinfo {TYPE_1__ cfg; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 void* IOV_READ (struct pci_devinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PCIR_SRIOV_CTL ; 
 int /*<<< orphan*/  PCIR_SRIOV_PAGE_SIZE ; 

void
pci_iov_cfg_save(device_t dev, struct pci_devinfo *dinfo)
{
	struct pcicfg_iov *iov;

	iov = dinfo->cfg.iov;

	iov->iov_page_size = IOV_READ(dinfo, PCIR_SRIOV_PAGE_SIZE, 4);
	iov->iov_ctl = IOV_READ(dinfo, PCIR_SRIOV_CTL, 2);
}