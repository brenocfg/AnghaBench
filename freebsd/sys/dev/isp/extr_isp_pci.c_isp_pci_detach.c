#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/ * ptr; } ;
struct TYPE_12__ {TYPE_2__ pc; } ;
struct TYPE_13__ {int isp_nirq; int /*<<< orphan*/  isp_lock; TYPE_3__ isp_osinfo; int /*<<< orphan*/ * isp_param; } ;
struct isp_pcisoftc {TYPE_4__ pci_isp; scalar_t__ regs2; int /*<<< orphan*/  rgd2; int /*<<< orphan*/  rtp2; scalar_t__ regs1; int /*<<< orphan*/  rgd1; int /*<<< orphan*/  rtp1; scalar_t__ regs; int /*<<< orphan*/  rgd; int /*<<< orphan*/  rtp; scalar_t__ msicount; TYPE_1__* irq; } ;
typedef  TYPE_4__ ispsoftc_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_10__ {scalar_t__ irq; int /*<<< orphan*/  iqd; int /*<<< orphan*/  ih; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_LOCK (TYPE_4__*) ; 
 int /*<<< orphan*/  ISP_UNLOCK (TYPE_4__*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct isp_pcisoftc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int isp_detach (TYPE_4__*) ; 
 int /*<<< orphan*/  isp_pci_mbxdmafree (TYPE_4__*) ; 
 int /*<<< orphan*/  isp_shutdown (TYPE_4__*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
isp_pci_detach(device_t dev)
{
	struct isp_pcisoftc *pcs = device_get_softc(dev);
	ispsoftc_t *isp = &pcs->pci_isp;
	int i, status;

	status = isp_detach(isp);
	if (status)
		return (status);
	ISP_LOCK(isp);
	isp_shutdown(isp);
	ISP_UNLOCK(isp);
	for (i = 0; i < isp->isp_nirq; i++) {
		(void) bus_teardown_intr(dev, pcs->irq[i].irq, pcs->irq[i].ih);
		(void) bus_release_resource(dev, SYS_RES_IRQ, pcs->irq[i].iqd,
		    pcs->irq[i].irq);
	}
	if (pcs->msicount)
		pci_release_msi(dev);
	(void) bus_release_resource(dev, pcs->rtp, pcs->rgd, pcs->regs);
	if (pcs->regs1)
		(void) bus_release_resource(dev, pcs->rtp1, pcs->rgd1, pcs->regs1);
	if (pcs->regs2)
		(void) bus_release_resource(dev, pcs->rtp2, pcs->rgd2, pcs->regs2);
	isp_pci_mbxdmafree(isp);
	if (pcs->pci_isp.isp_param) {
		free(pcs->pci_isp.isp_param, M_DEVBUF);
		pcs->pci_isp.isp_param = NULL;
	}
	if (pcs->pci_isp.isp_osinfo.pc.ptr) {
		free(pcs->pci_isp.isp_osinfo.pc.ptr, M_DEVBUF);
		pcs->pci_isp.isp_osinfo.pc.ptr = NULL;
	}
	mtx_destroy(&isp->isp_lock);
	return (0);
}