#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_3__ {int pcie_location; } ;
struct TYPE_4__ {TYPE_1__ pcie; } ;
struct pci_devinfo {TYPE_2__ cfg; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCIEM_CTL_MAX_PAYLOAD ; 
 scalar_t__ PCIER_DEVICE_CTL ; 
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,scalar_t__,int) ; 

int
pci_get_max_payload(device_t dev)
{
	struct pci_devinfo *dinfo = device_get_ivars(dev);
	int cap;
	uint16_t val;

	cap = dinfo->cfg.pcie.pcie_location;
	if (cap == 0)
		return (0);
	val = pci_read_config(dev, cap + PCIER_DEVICE_CTL, 2);
	val &= PCIEM_CTL_MAX_PAYLOAD;
	val >>= 5;
	return (1 << (val + 7));
}