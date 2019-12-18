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
typedef  int uint32_t ;
struct TYPE_2__ {int flags; int device; int vendor; int /*<<< orphan*/  func; int /*<<< orphan*/  slot; int /*<<< orphan*/  bus; } ;
struct pci_devinfo {TYPE_1__ cfg; } ;
typedef  TYPE_1__ pcicfgregs ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCIB_READ_CONFIG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int PCICFG_VF ; 
 int PCIR_DEVICE ; 
 int PCIR_VENDOR ; 
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

uint32_t
pci_read_config_method(device_t dev, device_t child, int reg, int width)
{
	struct pci_devinfo *dinfo = device_get_ivars(child);
	pcicfgregs *cfg = &dinfo->cfg;

#ifdef PCI_IOV
	/*
	 * SR-IOV VFs don't implement the VID or DID registers, so we have to
	 * emulate them here.
	 */
	if (cfg->flags & PCICFG_VF) {
		if (reg == PCIR_VENDOR) {
			switch (width) {
			case 4:
				return (cfg->device << 16 | cfg->vendor);
			case 2:
				return (cfg->vendor);
			case 1:
				return (cfg->vendor & 0xff);
			default:
				return (0xffffffff);
			}
		} else if (reg == PCIR_DEVICE) {
			switch (width) {
			/* Note that an unaligned 4-byte read is an error. */
			case 2:
				return (cfg->device);
			case 1:
				return (cfg->device & 0xff);
			default:
				return (0xffffffff);
			}
		}
	}
#endif

	return (PCIB_READ_CONFIG(device_get_parent(dev),
	    cfg->bus, cfg->slot, cfg->func, reg, width));
}