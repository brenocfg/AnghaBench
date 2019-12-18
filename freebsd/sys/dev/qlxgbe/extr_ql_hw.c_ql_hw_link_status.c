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
struct TYPE_4__ {int link_speed; int module_type; int link_faults; int /*<<< orphan*/  cable_length; scalar_t__ autoneg; scalar_t__ fduplex; scalar_t__ link_up; int /*<<< orphan*/  cable_oui; } ;
struct TYPE_5__ {int /*<<< orphan*/  pci_dev; TYPE_1__ hw; } ;
typedef  TYPE_2__ qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 

void
ql_hw_link_status(qla_host_t *ha)
{
	device_printf(ha->pci_dev, "cable_oui\t\t 0x%08x\n", ha->hw.cable_oui);

	if (ha->hw.link_up) {
		device_printf(ha->pci_dev, "link Up\n");
	} else {
		device_printf(ha->pci_dev, "link Down\n");
	}

	if (ha->hw.fduplex) {
		device_printf(ha->pci_dev, "Full Duplex\n");
	} else {
		device_printf(ha->pci_dev, "Half Duplex\n");
	}

	if (ha->hw.autoneg) {
		device_printf(ha->pci_dev, "Auto Negotiation Enabled\n");
	} else {
		device_printf(ha->pci_dev, "Auto Negotiation Disabled\n");
	}

	switch (ha->hw.link_speed) {
	case 0x710:
		device_printf(ha->pci_dev, "link speed\t\t 10Gps\n");
		break;

	case 0x3E8:
		device_printf(ha->pci_dev, "link speed\t\t 1Gps\n");
		break;

	case 0x64:
		device_printf(ha->pci_dev, "link speed\t\t 100Mbps\n");
		break;

	default:
		device_printf(ha->pci_dev, "link speed\t\t Unknown\n");
		break;
	}

	switch (ha->hw.module_type) {

	case 0x01:
		device_printf(ha->pci_dev, "Module Type 10GBase-LRM\n");
		break;

	case 0x02:
		device_printf(ha->pci_dev, "Module Type 10GBase-LR\n");
		break;

	case 0x03:
		device_printf(ha->pci_dev, "Module Type 10GBase-SR\n");
		break;

	case 0x04:
		device_printf(ha->pci_dev,
			"Module Type 10GE Passive Copper(Compliant)[%d m]\n",
			ha->hw.cable_length);
		break;

	case 0x05:
		device_printf(ha->pci_dev, "Module Type 10GE Active"
			" Limiting Copper(Compliant)[%d m]\n",
			ha->hw.cable_length);
		break;

	case 0x06:
		device_printf(ha->pci_dev,
			"Module Type 10GE Passive Copper"
			" (Legacy, Best Effort)[%d m]\n",
			ha->hw.cable_length);
		break;

	case 0x07:
		device_printf(ha->pci_dev, "Module Type 1000Base-SX\n");
		break;

	case 0x08:
		device_printf(ha->pci_dev, "Module Type 1000Base-LX\n");
		break;

	case 0x09:
		device_printf(ha->pci_dev, "Module Type 1000Base-CX\n");
		break;

	case 0x0A:
		device_printf(ha->pci_dev, "Module Type 1000Base-T\n");
		break;

	case 0x0B:
		device_printf(ha->pci_dev, "Module Type 1GE Passive Copper"
			"(Legacy, Best Effort)\n");
		break;

	default:
		device_printf(ha->pci_dev, "Unknown Module Type 0x%x\n",
			ha->hw.module_type);
		break;
	}

	if (ha->hw.link_faults == 1)
		device_printf(ha->pci_dev, "SFP Power Fault\n");
}