#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  u_int ;
struct pci_devinfo {int dummy; } ;
struct TYPE_5__ {scalar_t__ intline; } ;
struct TYPE_6__ {TYPE_2__ cfg; } ;
struct TYPE_4__ {int obd_node; int /*<<< orphan*/ * obd_model; int /*<<< orphan*/ * obd_type; int /*<<< orphan*/ * obd_compat; int /*<<< orphan*/ * obd_name; } ;
struct ofw_pcibus_devinfo {TYPE_3__ opd_dinfo; TYPE_1__ opd_obdinfo; int /*<<< orphan*/ * opd_dma_tag; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int PCIB_MAXSLOTS (int /*<<< orphan*/ ) ; 
 int PCIB_READ_CONFIG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PCIB_WRITE_CONFIG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int PCIM_HDRTYPE ; 
 int PCIM_MFDEV ; 
 int /*<<< orphan*/  PCIR_HDRTYPE ; 
 int /*<<< orphan*/  PCIR_INTLINE ; 
 int PCI_FUNCMAX ; 
 scalar_t__ PCI_INVALID_IRQ ; 
 int PCI_MAXHDRTYPE ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_add_child (int /*<<< orphan*/ ,struct pci_devinfo*) ; 
 int /*<<< orphan*/ * pci_find_dbsf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ pci_read_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
ofw_pcibus_enum_bus(device_t dev, u_int domain, u_int busno)
{
	device_t pcib;
	struct ofw_pcibus_devinfo *dinfo;
	int maxslots;
	int s, f, pcifunchigh;
	uint8_t hdrtype;

	pcib = device_get_parent(dev);

	maxslots = PCIB_MAXSLOTS(pcib);
	for (s = 0; s <= maxslots; s++) {
		pcifunchigh = 0;
		f = 0;
		DELAY(1);
		hdrtype = PCIB_READ_CONFIG(pcib, busno, s, f, PCIR_HDRTYPE, 1);
		if ((hdrtype & PCIM_HDRTYPE) > PCI_MAXHDRTYPE)
			continue;
		if (hdrtype & PCIM_MFDEV)
			pcifunchigh = PCI_FUNCMAX;
		for (f = 0; f <= pcifunchigh; f++) {
			/* Filter devices we have already added */
			if (pci_find_dbsf(domain, busno, s, f) != NULL)
				continue;

			dinfo = (struct ofw_pcibus_devinfo *)pci_read_device(
			    pcib, dev, domain, busno, s, f);
			if (dinfo == NULL)
				continue;

			dinfo->opd_dma_tag = NULL;
			dinfo->opd_obdinfo.obd_node = -1;

			dinfo->opd_obdinfo.obd_name = NULL;
			dinfo->opd_obdinfo.obd_compat = NULL;
			dinfo->opd_obdinfo.obd_type = NULL;
			dinfo->opd_obdinfo.obd_model = NULL;

			/*
			 * For non OFW-devices, don't believe 0 
			 * for an interrupt.
			 */
			if (dinfo->opd_dinfo.cfg.intline == 0) {
				dinfo->opd_dinfo.cfg.intline = PCI_INVALID_IRQ;
				PCIB_WRITE_CONFIG(pcib, busno, s, f, 
				    PCIR_INTLINE, PCI_INVALID_IRQ, 1);
			}

			pci_add_child(dev, (struct pci_devinfo *)dinfo);
		}
	}
}