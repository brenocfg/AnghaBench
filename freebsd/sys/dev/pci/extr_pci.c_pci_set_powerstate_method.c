#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_4__ {scalar_t__ pp_cap; int /*<<< orphan*/  pp_status; } ;
struct TYPE_5__ {TYPE_1__ pp; } ;
struct pci_devinfo {TYPE_2__ cfg; } ;
typedef  TYPE_2__ pcicfgregs ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int PCIM_PCAP_D1SUPP ; 
 int PCIM_PCAP_D2SUPP ; 
 int PCIM_PSTAT_D0 ; 
 int PCIM_PSTAT_D1 ; 
 int PCIM_PSTAT_D2 ; 
 int PCIM_PSTAT_D3 ; 
 int PCIM_PSTAT_DMASK ; 
#define  PCI_POWERSTATE_D0 131 
#define  PCI_POWERSTATE_D1 130 
#define  PCI_POWERSTATE_D2 129 
#define  PCI_POWERSTATE_D3 128 
 int PCI_READ_CONFIG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PCI_WRITE_CONFIG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ bootverbose ; 
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int pci_get_powerstate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_printf (TYPE_2__*,char*,int,int) ; 

int
pci_set_powerstate_method(device_t dev, device_t child, int state)
{
	struct pci_devinfo *dinfo = device_get_ivars(child);
	pcicfgregs *cfg = &dinfo->cfg;
	uint16_t status;
	int oldstate, highest, delay;

	if (cfg->pp.pp_cap == 0)
		return (EOPNOTSUPP);

	/*
	 * Optimize a no state change request away.  While it would be OK to
	 * write to the hardware in theory, some devices have shown odd
	 * behavior when going from D3 -> D3.
	 */
	oldstate = pci_get_powerstate(child);
	if (oldstate == state)
		return (0);

	/*
	 * The PCI power management specification states that after a state
	 * transition between PCI power states, system software must
	 * guarantee a minimal delay before the function accesses the device.
	 * Compute the worst case delay that we need to guarantee before we
	 * access the device.  Many devices will be responsive much more
	 * quickly than this delay, but there are some that don't respond
	 * instantly to state changes.  Transitions to/from D3 state require
	 * 10ms, while D2 requires 200us, and D0/1 require none.  The delay
	 * is done below with DELAY rather than a sleeper function because
	 * this function can be called from contexts where we cannot sleep.
	 */
	highest = (oldstate > state) ? oldstate : state;
	if (highest == PCI_POWERSTATE_D3)
	    delay = 10000;
	else if (highest == PCI_POWERSTATE_D2)
	    delay = 200;
	else
	    delay = 0;
	status = PCI_READ_CONFIG(dev, child, cfg->pp.pp_status, 2)
	    & ~PCIM_PSTAT_DMASK;
	switch (state) {
	case PCI_POWERSTATE_D0:
		status |= PCIM_PSTAT_D0;
		break;
	case PCI_POWERSTATE_D1:
		if ((cfg->pp.pp_cap & PCIM_PCAP_D1SUPP) == 0)
			return (EOPNOTSUPP);
		status |= PCIM_PSTAT_D1;
		break;
	case PCI_POWERSTATE_D2:
		if ((cfg->pp.pp_cap & PCIM_PCAP_D2SUPP) == 0)
			return (EOPNOTSUPP);
		status |= PCIM_PSTAT_D2;
		break;
	case PCI_POWERSTATE_D3:
		status |= PCIM_PSTAT_D3;
		break;
	default:
		return (EINVAL);
	}

	if (bootverbose)
		pci_printf(cfg, "Transition from D%d to D%d\n", oldstate,
		    state);

	PCI_WRITE_CONFIG(dev, child, cfg->pp.pp_status, status, 2);
	if (delay)
		DELAY(delay);
	return (0);
}