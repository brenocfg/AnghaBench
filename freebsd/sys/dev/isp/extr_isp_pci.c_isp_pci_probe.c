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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AMI_RAID_SUBVENDOR_ID ; 
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int ISP_CORE_VERSION_MAJOR ; 
 int ISP_CORE_VERSION_MINOR ; 
 int ISP_PLATFORM_VERSION_MAJOR ; 
 int ISP_PLATFORM_VERSION_MINOR ; 
#define  PCI_QLOGIC_ISP10160 150 
#define  PCI_QLOGIC_ISP1020 149 
#define  PCI_QLOGIC_ISP1080 148 
#define  PCI_QLOGIC_ISP12160 147 
#define  PCI_QLOGIC_ISP1240 146 
#define  PCI_QLOGIC_ISP1280 145 
#define  PCI_QLOGIC_ISP2031 144 
#define  PCI_QLOGIC_ISP2100 143 
#define  PCI_QLOGIC_ISP2200 142 
#define  PCI_QLOGIC_ISP2300 141 
#define  PCI_QLOGIC_ISP2312 140 
#define  PCI_QLOGIC_ISP2322 139 
#define  PCI_QLOGIC_ISP2422 138 
#define  PCI_QLOGIC_ISP2432 137 
#define  PCI_QLOGIC_ISP2532 136 
#define  PCI_QLOGIC_ISP2684 135 
#define  PCI_QLOGIC_ISP2692 134 
#define  PCI_QLOGIC_ISP2714 133 
#define  PCI_QLOGIC_ISP2722 132 
#define  PCI_QLOGIC_ISP5432 131 
#define  PCI_QLOGIC_ISP6312 130 
#define  PCI_QLOGIC_ISP6322 129 
#define  PCI_QLOGIC_ISP8031 128 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ isp_announced ; 
 int pci_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_subvendor (int /*<<< orphan*/ ) ; 
 int pci_get_vendor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int) ; 

__attribute__((used)) static int
isp_pci_probe(device_t dev)
{
	switch ((pci_get_device(dev) << 16) | (pci_get_vendor(dev))) {
	case PCI_QLOGIC_ISP1020:
		device_set_desc(dev, "Qlogic ISP 1020/1040 PCI SCSI Adapter");
		break;
	case PCI_QLOGIC_ISP1080:
		device_set_desc(dev, "Qlogic ISP 1080 PCI SCSI Adapter");
		break;
	case PCI_QLOGIC_ISP1240:
		device_set_desc(dev, "Qlogic ISP 1240 PCI SCSI Adapter");
		break;
	case PCI_QLOGIC_ISP1280:
		device_set_desc(dev, "Qlogic ISP 1280 PCI SCSI Adapter");
		break;
	case PCI_QLOGIC_ISP10160:
		device_set_desc(dev, "Qlogic ISP 10160 PCI SCSI Adapter");
		break;
	case PCI_QLOGIC_ISP12160:
		if (pci_get_subvendor(dev) == AMI_RAID_SUBVENDOR_ID) {
			return (ENXIO);
		}
		device_set_desc(dev, "Qlogic ISP 12160 PCI SCSI Adapter");
		break;
	case PCI_QLOGIC_ISP2100:
		device_set_desc(dev, "Qlogic ISP 2100 PCI FC-AL Adapter");
		break;
	case PCI_QLOGIC_ISP2200:
		device_set_desc(dev, "Qlogic ISP 2200 PCI FC-AL Adapter");
		break;
	case PCI_QLOGIC_ISP2300:
		device_set_desc(dev, "Qlogic ISP 2300 PCI FC-AL Adapter");
		break;
	case PCI_QLOGIC_ISP2312:
		device_set_desc(dev, "Qlogic ISP 2312 PCI FC-AL Adapter");
		break;
	case PCI_QLOGIC_ISP2322:
		device_set_desc(dev, "Qlogic ISP 2322 PCI FC-AL Adapter");
		break;
	case PCI_QLOGIC_ISP2422:
		device_set_desc(dev, "Qlogic ISP 2422 PCI FC-AL Adapter");
		break;
	case PCI_QLOGIC_ISP2432:
		device_set_desc(dev, "Qlogic ISP 2432 PCI FC-AL Adapter");
		break;
	case PCI_QLOGIC_ISP2532:
		device_set_desc(dev, "Qlogic ISP 2532 PCI FC-AL Adapter");
		break;
	case PCI_QLOGIC_ISP5432:
		device_set_desc(dev, "Qlogic ISP 5432 PCI FC-AL Adapter");
		break;
	case PCI_QLOGIC_ISP6312:
		device_set_desc(dev, "Qlogic ISP 6312 PCI FC-AL Adapter");
		break;
	case PCI_QLOGIC_ISP6322:
		device_set_desc(dev, "Qlogic ISP 6322 PCI FC-AL Adapter");
		break;
	case PCI_QLOGIC_ISP2031:
		device_set_desc(dev, "Qlogic ISP 2031 PCI FC-AL Adapter");
		break;
	case PCI_QLOGIC_ISP8031:
		device_set_desc(dev, "Qlogic ISP 8031 PCI FCoE Adapter");
		break;
	case PCI_QLOGIC_ISP2684:
		device_set_desc(dev, "Qlogic ISP 2684 PCI FC Adapter");
		break;
	case PCI_QLOGIC_ISP2692:
		device_set_desc(dev, "Qlogic ISP 2692 PCI FC Adapter");
		break;
	case PCI_QLOGIC_ISP2714:
		device_set_desc(dev, "Qlogic ISP 2714 PCI FC Adapter");
		break;
	case PCI_QLOGIC_ISP2722:
		device_set_desc(dev, "Qlogic ISP 2722 PCI FC Adapter");
		break;
	default:
		return (ENXIO);
	}
	if (isp_announced == 0 && bootverbose) {
		printf("Qlogic ISP Driver, FreeBSD Version %d.%d, "
		    "Core Version %d.%d\n",
		    ISP_PLATFORM_VERSION_MAJOR, ISP_PLATFORM_VERSION_MINOR,
		    ISP_CORE_VERSION_MAJOR, ISP_CORE_VERSION_MINOR);
		isp_announced++;
	}
	/*
	 * XXXX: Here is where we might load the f/w module
	 * XXXX: (or increase a reference count to it).
	 */
	return (BUS_PROBE_DEFAULT);
}