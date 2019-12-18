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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/ * nid; } ;
struct TYPE_6__ {TYPE_2__ lan; } ;
struct TYPE_4__ {int /*<<< orphan*/  cfg; } ;
struct cardbus_devinfo {int fepresent; TYPE_3__ funce; TYPE_1__ pci; } ;
typedef  int /*<<< orphan*/  pcicfgregs ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int PCCARD_TPLFE_TYPE_LAN_NID ; 
#define  PCI_IVAR_ETHADDR 128 
 struct cardbus_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int pci_read_ivar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,uintptr_t*) ; 

__attribute__((used)) static int
cardbus_read_ivar(device_t cbdev, device_t child, int which, uintptr_t *result)
{
	struct cardbus_devinfo *dinfo;
	pcicfgregs *cfg;

	dinfo = device_get_ivars(child);
	cfg = &dinfo->pci.cfg;

	switch (which) {
	case PCI_IVAR_ETHADDR:
		/*
		 * The generic accessor doesn't deal with failure, so
		 * we set the return value, then return an error.
		 */
		if (dinfo->fepresent & (1 << PCCARD_TPLFE_TYPE_LAN_NID)) {
			*((uint8_t **) result) = dinfo->funce.lan.nid;
			break;
		}
		*((uint8_t **) result) = NULL;
		return (EINVAL);
	default:
		return (pci_read_ivar(cbdev, child, which, result));
	}
	return 0;
}