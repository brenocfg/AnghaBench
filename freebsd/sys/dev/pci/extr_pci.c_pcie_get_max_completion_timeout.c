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
struct TYPE_3__ {int pcie_location; int pcie_flags; } ;
struct TYPE_4__ {TYPE_1__ pcie; } ;
struct pci_devinfo {TYPE_2__ cfg; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCIEM_CAP2_COMP_TIMO_RANGES ; 
#define  PCIEM_CTL2_COMP_TIMO_100US 135 
#define  PCIEM_CTL2_COMP_TIMO_10MS 134 
#define  PCIEM_CTL2_COMP_TIMO_13S 133 
#define  PCIEM_CTL2_COMP_TIMO_210MS 132 
#define  PCIEM_CTL2_COMP_TIMO_3500MS 131 
#define  PCIEM_CTL2_COMP_TIMO_55MS 130 
#define  PCIEM_CTL2_COMP_TIMO_64S 129 
#define  PCIEM_CTL2_COMP_TIMO_900MS 128 
 int PCIEM_CTL2_COMP_TIMO_VAL ; 
 int PCIEM_FLAGS_VERSION ; 
 scalar_t__ PCIER_DEVICE_CAP2 ; 
 scalar_t__ PCIER_DEVICE_CTL2 ; 
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,scalar_t__,int) ; 

int
pcie_get_max_completion_timeout(device_t dev)
{
	struct pci_devinfo *dinfo = device_get_ivars(dev);
	int cap;

	cap = dinfo->cfg.pcie.pcie_location;
	if (cap == 0)
		return (0);

	/*
	 * Functions using the 1.x spec use the default timeout range of
	 * 50 microseconds to 50 milliseconds.  Functions that do not
	 * support programmable timeouts also use this range.
	 */
	if ((dinfo->cfg.pcie.pcie_flags & PCIEM_FLAGS_VERSION) < 2 ||
	    (pci_read_config(dev, cap + PCIER_DEVICE_CAP2, 4) &
	    PCIEM_CAP2_COMP_TIMO_RANGES) == 0)
		return (50 * 1000);

	switch (pci_read_config(dev, cap + PCIER_DEVICE_CTL2, 2) &
	    PCIEM_CTL2_COMP_TIMO_VAL) {
	case PCIEM_CTL2_COMP_TIMO_100US:
		return (100);
	case PCIEM_CTL2_COMP_TIMO_10MS:
		return (10 * 1000);
	case PCIEM_CTL2_COMP_TIMO_55MS:
		return (55 * 1000);
	case PCIEM_CTL2_COMP_TIMO_210MS:
		return (210 * 1000);
	case PCIEM_CTL2_COMP_TIMO_900MS:
		return (900 * 1000);
	case PCIEM_CTL2_COMP_TIMO_3500MS:
		return (3500 * 1000);
	case PCIEM_CTL2_COMP_TIMO_13S:
		return (13 * 1000 * 1000);
	case PCIEM_CTL2_COMP_TIMO_64S:
		return (64 * 1000 * 1000);
	default:
		return (50 * 1000);
	}
}