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
struct TYPE_3__ {scalar_t__ pp_cap; int /*<<< orphan*/  pp_status; } ;
struct TYPE_4__ {TYPE_1__ pp; } ;
struct pci_devinfo {TYPE_2__ cfg; } ;
typedef  TYPE_2__ pcicfgregs ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
#define  PCIM_PSTAT_D0 131 
#define  PCIM_PSTAT_D1 130 
#define  PCIM_PSTAT_D2 129 
#define  PCIM_PSTAT_D3 128 
 int PCIM_PSTAT_DMASK ; 
 int PCI_POWERSTATE_D0 ; 
 int PCI_POWERSTATE_D1 ; 
 int PCI_POWERSTATE_D2 ; 
 int PCI_POWERSTATE_D3 ; 
 int PCI_POWERSTATE_UNKNOWN ; 
 int PCI_READ_CONFIG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 

int
pci_get_powerstate_method(device_t dev, device_t child)
{
	struct pci_devinfo *dinfo = device_get_ivars(child);
	pcicfgregs *cfg = &dinfo->cfg;
	uint16_t status;
	int result;

	if (cfg->pp.pp_cap != 0) {
		status = PCI_READ_CONFIG(dev, child, cfg->pp.pp_status, 2);
		switch (status & PCIM_PSTAT_DMASK) {
		case PCIM_PSTAT_D0:
			result = PCI_POWERSTATE_D0;
			break;
		case PCIM_PSTAT_D1:
			result = PCI_POWERSTATE_D1;
			break;
		case PCIM_PSTAT_D2:
			result = PCI_POWERSTATE_D2;
			break;
		case PCIM_PSTAT_D3:
			result = PCI_POWERSTATE_D3;
			break;
		default:
			result = PCI_POWERSTATE_UNKNOWN;
			break;
		}
	} else {
		/* No support, device is always at D0 */
		result = PCI_POWERSTATE_D0;
	}
	return (result);
}