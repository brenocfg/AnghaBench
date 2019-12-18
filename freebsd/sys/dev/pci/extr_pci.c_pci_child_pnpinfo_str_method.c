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
struct TYPE_2__ {int vendor; int device; int subvendor; int subdevice; int baseclass; int subclass; int /*<<< orphan*/  progif; } ;
struct pci_devinfo {TYPE_1__ cfg; } ;
typedef  TYPE_1__ pcicfgregs ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int,int,int,int,int,int,int /*<<< orphan*/ ) ; 

int
pci_child_pnpinfo_str_method(device_t dev, device_t child, char *buf,
    size_t buflen)
{
	struct pci_devinfo *dinfo;
	pcicfgregs *cfg;

	dinfo = device_get_ivars(child);
	cfg = &dinfo->cfg;
	snprintf(buf, buflen, "vendor=0x%04x device=0x%04x subvendor=0x%04x "
	    "subdevice=0x%04x class=0x%02x%02x%02x", cfg->vendor, cfg->device,
	    cfg->subvendor, cfg->subdevice, cfg->baseclass, cfg->subclass,
	    cfg->progif);
	return (0);
}