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
struct TYPE_2__ {uintptr_t intpin; } ;
struct pci_devinfo {TYPE_1__ cfg; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
#define  PCI_IVAR_BUS 143 
#define  PCI_IVAR_CLASS 142 
#define  PCI_IVAR_DEVICE 141 
#define  PCI_IVAR_DEVID 140 
#define  PCI_IVAR_DOMAIN 139 
#define  PCI_IVAR_ETHADDR 138 
#define  PCI_IVAR_FUNCTION 137 
#define  PCI_IVAR_INTPIN 136 
#define  PCI_IVAR_IRQ 135 
#define  PCI_IVAR_PROGIF 134 
#define  PCI_IVAR_REVID 133 
#define  PCI_IVAR_SLOT 132 
#define  PCI_IVAR_SUBCLASS 131 
#define  PCI_IVAR_SUBDEVICE 130 
#define  PCI_IVAR_SUBVENDOR 129 
#define  PCI_IVAR_VENDOR 128 
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 

int
pci_write_ivar(device_t dev, device_t child, int which, uintptr_t value)
{
	struct pci_devinfo *dinfo;

	dinfo = device_get_ivars(child);

	switch (which) {
	case PCI_IVAR_INTPIN:
		dinfo->cfg.intpin = value;
		return (0);
	case PCI_IVAR_ETHADDR:
	case PCI_IVAR_SUBVENDOR:
	case PCI_IVAR_SUBDEVICE:
	case PCI_IVAR_VENDOR:
	case PCI_IVAR_DEVICE:
	case PCI_IVAR_DEVID:
	case PCI_IVAR_CLASS:
	case PCI_IVAR_SUBCLASS:
	case PCI_IVAR_PROGIF:
	case PCI_IVAR_REVID:
	case PCI_IVAR_IRQ:
	case PCI_IVAR_DOMAIN:
	case PCI_IVAR_BUS:
	case PCI_IVAR_SLOT:
	case PCI_IVAR_FUNCTION:
		return (EINVAL);	/* disallow for now */

	default:
		return (ENOENT);
	}
}