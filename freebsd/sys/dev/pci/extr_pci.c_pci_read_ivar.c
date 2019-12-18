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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {uintptr_t subvendor; uintptr_t subdevice; uintptr_t vendor; uintptr_t device; uintptr_t baseclass; uintptr_t subclass; uintptr_t progif; uintptr_t revid; uintptr_t intpin; uintptr_t intline; uintptr_t domain; uintptr_t bus; uintptr_t slot; uintptr_t func; uintptr_t cmdreg; uintptr_t cachelnsz; uintptr_t mingnt; uintptr_t maxlat; uintptr_t lattimer; int /*<<< orphan*/  hdrtype; } ;
struct pci_devinfo {TYPE_1__ cfg; } ;
typedef  TYPE_1__ pcicfgregs ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  PCIM_HDRTYPE_NORMAL ; 
#define  PCI_IVAR_BUS 148 
#define  PCI_IVAR_CACHELNSZ 147 
#define  PCI_IVAR_CLASS 146 
#define  PCI_IVAR_CMDREG 145 
#define  PCI_IVAR_DEVICE 144 
#define  PCI_IVAR_DEVID 143 
#define  PCI_IVAR_DOMAIN 142 
#define  PCI_IVAR_ETHADDR 141 
#define  PCI_IVAR_FUNCTION 140 
#define  PCI_IVAR_INTPIN 139 
#define  PCI_IVAR_IRQ 138 
#define  PCI_IVAR_LATTIMER 137 
#define  PCI_IVAR_MAXLAT 136 
#define  PCI_IVAR_MINGNT 135 
#define  PCI_IVAR_PROGIF 134 
#define  PCI_IVAR_REVID 133 
#define  PCI_IVAR_SLOT 132 
#define  PCI_IVAR_SUBCLASS 131 
#define  PCI_IVAR_SUBDEVICE 130 
#define  PCI_IVAR_SUBVENDOR 129 
#define  PCI_IVAR_VENDOR 128 
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 

int
pci_read_ivar(device_t dev, device_t child, int which, uintptr_t *result)
{
	struct pci_devinfo *dinfo;
	pcicfgregs *cfg;

	dinfo = device_get_ivars(child);
	cfg = &dinfo->cfg;

	switch (which) {
	case PCI_IVAR_ETHADDR:
		/*
		 * The generic accessor doesn't deal with failure, so
		 * we set the return value, then return an error.
		 */
		*((uint8_t **) result) = NULL;
		return (EINVAL);
	case PCI_IVAR_SUBVENDOR:
		*result = cfg->subvendor;
		break;
	case PCI_IVAR_SUBDEVICE:
		*result = cfg->subdevice;
		break;
	case PCI_IVAR_VENDOR:
		*result = cfg->vendor;
		break;
	case PCI_IVAR_DEVICE:
		*result = cfg->device;
		break;
	case PCI_IVAR_DEVID:
		*result = (cfg->device << 16) | cfg->vendor;
		break;
	case PCI_IVAR_CLASS:
		*result = cfg->baseclass;
		break;
	case PCI_IVAR_SUBCLASS:
		*result = cfg->subclass;
		break;
	case PCI_IVAR_PROGIF:
		*result = cfg->progif;
		break;
	case PCI_IVAR_REVID:
		*result = cfg->revid;
		break;
	case PCI_IVAR_INTPIN:
		*result = cfg->intpin;
		break;
	case PCI_IVAR_IRQ:
		*result = cfg->intline;
		break;
	case PCI_IVAR_DOMAIN:
		*result = cfg->domain;
		break;
	case PCI_IVAR_BUS:
		*result = cfg->bus;
		break;
	case PCI_IVAR_SLOT:
		*result = cfg->slot;
		break;
	case PCI_IVAR_FUNCTION:
		*result = cfg->func;
		break;
	case PCI_IVAR_CMDREG:
		*result = cfg->cmdreg;
		break;
	case PCI_IVAR_CACHELNSZ:
		*result = cfg->cachelnsz;
		break;
	case PCI_IVAR_MINGNT:
		if (cfg->hdrtype != PCIM_HDRTYPE_NORMAL) {
			*result = -1;
			return (EINVAL);
		}
		*result = cfg->mingnt;
		break;
	case PCI_IVAR_MAXLAT:
		if (cfg->hdrtype != PCIM_HDRTYPE_NORMAL) {
			*result = -1;
			return (EINVAL);
		}
		*result = cfg->maxlat;
		break;
	case PCI_IVAR_LATTIMER:
		*result = cfg->lattimer;
		break;
	default:
		return (ENOENT);
	}
	return (0);
}