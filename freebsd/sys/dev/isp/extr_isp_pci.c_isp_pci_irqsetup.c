#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct isp_pcisoftc {int msicount; TYPE_2__* irq; } ;
struct TYPE_11__ {int /*<<< orphan*/  dev; } ;
struct TYPE_13__ {int isp_nirq; TYPE_1__ isp_osinfo; } ;
typedef  TYPE_3__ ispsoftc_t ;
typedef  int /*<<< orphan*/  driver_intr_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_12__ {int iqd; int /*<<< orphan*/  ih; int /*<<< orphan*/ * irq; } ;

/* Variables and functions */
 scalar_t__ ISP_CAP_MSIX (TYPE_3__*) ; 
 int /*<<< orphan*/  ISP_IFLAGS ; 
 int /*<<< orphan*/  ISP_LOCK (TYPE_3__*) ; 
 int ISP_MAX_IRQS ; 
 int /*<<< orphan*/  ISP_UNLOCK (TYPE_3__*) ; 
 scalar_t__ IS_25XX (TYPE_3__*) ; 
 scalar_t__ IS_26XX (TYPE_3__*) ; 
 int MAX (int,int) ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  bus_describe_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 struct isp_pcisoftc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 void* imin (int,int) ; 
 int /*<<< orphan*/ * isp_platform_intr ; 
 int /*<<< orphan*/ * isp_platform_intr_atio ; 
 int /*<<< orphan*/ * isp_platform_intr_resp ; 
 scalar_t__ pci_alloc_msi (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ pci_alloc_msix (int /*<<< orphan*/ ,int*) ; 
 int pci_msi_count (int /*<<< orphan*/ ) ; 
 int pci_msix_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_int_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 

__attribute__((used)) static int
isp_pci_irqsetup(ispsoftc_t *isp)
{
	device_t dev = isp->isp_osinfo.dev;
	struct isp_pcisoftc *pcs = device_get_softc(dev);
	driver_intr_t *f;
	int i, max_irq;

	/* Allocate IRQs only once. */
	if (isp->isp_nirq > 0)
		return (0);

	ISP_UNLOCK(isp);
	if (ISP_CAP_MSIX(isp)) {
		max_irq = IS_26XX(isp) ? 3 : (IS_25XX(isp) ? 2 : 0);
		resource_int_value(device_get_name(dev),
		    device_get_unit(dev), "msix", &max_irq);
		max_irq = imin(ISP_MAX_IRQS, max_irq);
		pcs->msicount = imin(pci_msix_count(dev), max_irq);
		if (pcs->msicount > 0 &&
		    pci_alloc_msix(dev, &pcs->msicount) != 0)
			pcs->msicount = 0;
	}
	if (pcs->msicount == 0) {
		max_irq = 1;
		resource_int_value(device_get_name(dev),
		    device_get_unit(dev), "msi", &max_irq);
		max_irq = imin(1, max_irq);
		pcs->msicount = imin(pci_msi_count(dev), max_irq);
		if (pcs->msicount > 0 &&
		    pci_alloc_msi(dev, &pcs->msicount) != 0)
			pcs->msicount = 0;
	}
	for (i = 0; i < MAX(1, pcs->msicount); i++) {
		pcs->irq[i].iqd = i + (pcs->msicount > 0);
		pcs->irq[i].irq = bus_alloc_resource_any(dev, SYS_RES_IRQ,
		    &pcs->irq[i].iqd, RF_ACTIVE | RF_SHAREABLE);
		if (pcs->irq[i].irq == NULL) {
			device_printf(dev, "could not allocate interrupt\n");
			break;
		}
		if (i == 0)
			f = isp_platform_intr;
		else if (i == 1)
			f = isp_platform_intr_resp;
		else
			f = isp_platform_intr_atio;
		if (bus_setup_intr(dev, pcs->irq[i].irq, ISP_IFLAGS, NULL,
		    f, isp, &pcs->irq[i].ih)) {
			device_printf(dev, "could not setup interrupt\n");
			(void) bus_release_resource(dev, SYS_RES_IRQ,
			    pcs->irq[i].iqd, pcs->irq[i].irq);
			break;
		}
		if (pcs->msicount > 1) {
			bus_describe_intr(dev, pcs->irq[i].irq, pcs->irq[i].ih,
			    "%d", i);
		}
		isp->isp_nirq = i + 1;
	}
	ISP_LOCK(isp);

	return (isp->isp_nirq == 0);
}