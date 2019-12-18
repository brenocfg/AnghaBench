#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
#define  BHND_DEVCLASS_CC 148 
#define  BHND_DEVCLASS_CC_B 147 
#define  BHND_DEVCLASS_CPU 146 
#define  BHND_DEVCLASS_ENET 145 
#define  BHND_DEVCLASS_ENET_MAC 144 
#define  BHND_DEVCLASS_ENET_PHY 143 
#define  BHND_DEVCLASS_EROM 142 
#define  BHND_DEVCLASS_INVALID 141 
#define  BHND_DEVCLASS_MEMC 140 
#define  BHND_DEVCLASS_NVRAM 139 
#define  BHND_DEVCLASS_OTHER 138 
#define  BHND_DEVCLASS_PCCARD 137 
#define  BHND_DEVCLASS_PCI 136 
#define  BHND_DEVCLASS_PCIE 135 
#define  BHND_DEVCLASS_PMU 134 
#define  BHND_DEVCLASS_RAM 133 
#define  BHND_DEVCLASS_SOC_BRIDGE 132 
#define  BHND_DEVCLASS_SOC_ROUTER 131 
#define  BHND_DEVCLASS_WLAN 130 
#define  BHND_DEVCLASS_WLAN_MAC 129 
#define  BHND_DEVCLASS_WLAN_PHY 128 
 int BHND_PROBE_BUS ; 
 int BHND_PROBE_CPU ; 
 int BHND_PROBE_DEFAULT ; 
 int BHND_PROBE_ORDER_EARLY ; 
 int BHND_PROBE_ORDER_FIRST ; 
 int BHND_PROBE_ORDER_LAST ; 
 int BHND_PROBE_ORDER_LATE ; 
 int BHND_PROBE_RESOURCE ; 
 int BHND_PROBE_ROOT ; 
 int /*<<< orphan*/  bhnd_bus_find_hostb_device (int /*<<< orphan*/ ) ; 
 int bhnd_get_class (int /*<<< orphan*/ ) ; 

int
bhnd_generic_get_probe_order(device_t dev, device_t child)
{
	switch (bhnd_get_class(child)) {
	case BHND_DEVCLASS_CC:
		/* Must be early enough to provide NVRAM access to the
		 * host bridge */
		return (BHND_PROBE_ROOT + BHND_PROBE_ORDER_FIRST);

	case BHND_DEVCLASS_CC_B:
		/* fall through */
	case BHND_DEVCLASS_PMU:
		return (BHND_PROBE_BUS + BHND_PROBE_ORDER_EARLY);

	case BHND_DEVCLASS_SOC_ROUTER:
		return (BHND_PROBE_BUS + BHND_PROBE_ORDER_LATE);

	case BHND_DEVCLASS_SOC_BRIDGE:
		return (BHND_PROBE_BUS + BHND_PROBE_ORDER_LAST);
		
	case BHND_DEVCLASS_CPU:
		return (BHND_PROBE_CPU + BHND_PROBE_ORDER_FIRST);

	case BHND_DEVCLASS_RAM:
		/* fall through */
	case BHND_DEVCLASS_MEMC:
		return (BHND_PROBE_CPU + BHND_PROBE_ORDER_EARLY);
		
	case BHND_DEVCLASS_NVRAM:
		return (BHND_PROBE_RESOURCE + BHND_PROBE_ORDER_EARLY);

	case BHND_DEVCLASS_PCI:
	case BHND_DEVCLASS_PCIE:
	case BHND_DEVCLASS_PCCARD:
	case BHND_DEVCLASS_ENET:
	case BHND_DEVCLASS_ENET_MAC:
	case BHND_DEVCLASS_ENET_PHY:
	case BHND_DEVCLASS_WLAN:
	case BHND_DEVCLASS_WLAN_MAC:
	case BHND_DEVCLASS_WLAN_PHY:
	case BHND_DEVCLASS_EROM:
	case BHND_DEVCLASS_OTHER:
	case BHND_DEVCLASS_INVALID:
		if (bhnd_bus_find_hostb_device(dev) == child)
			return (BHND_PROBE_ROOT + BHND_PROBE_ORDER_EARLY);

		return (BHND_PROBE_DEFAULT);
	default:
		return (BHND_PROBE_DEFAULT);
	}
}