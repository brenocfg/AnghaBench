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
struct bwn_pci_softc {int quirks; } ;
struct bhnd_core_info {int /*<<< orphan*/  unit; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
#define  BHND_DEVCLASS_ENET 133 
#define  BHND_DEVCLASS_ENET_MAC 132 
#define  BHND_DEVCLASS_ENET_PHY 131 
#define  BHND_DEVCLASS_SOFTMODEM 130 
#define  BHND_DEVCLASS_USB_HOST 129 
#define  BHND_DEVCLASS_WLAN 128 
 int BWN_QUIRK_ENET_HW_UNPOPULATED ; 
 int BWN_QUIRK_SOFTMODEM_UNPOPULATED ; 
 int BWN_QUIRK_USBH_UNPOPULATED ; 
 int BWN_QUIRK_WLAN_DUALCORE ; 
 int bhnd_core_class (struct bhnd_core_info*) ; 
 struct bwn_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
bwn_pci_is_core_disabled(device_t dev, device_t child,
    struct bhnd_core_info *core)
{
	struct bwn_pci_softc	*sc;

	sc = device_get_softc(dev);

	switch (bhnd_core_class(core)) {
	case BHND_DEVCLASS_WLAN:
		if (core->unit > 0 && !(sc->quirks & BWN_QUIRK_WLAN_DUALCORE))
			return (true);

		return (false);

	case BHND_DEVCLASS_ENET:
	case BHND_DEVCLASS_ENET_MAC:
	case BHND_DEVCLASS_ENET_PHY:
		return ((sc->quirks & BWN_QUIRK_ENET_HW_UNPOPULATED) != 0);
		
	case BHND_DEVCLASS_USB_HOST:
		return ((sc->quirks & BWN_QUIRK_USBH_UNPOPULATED) != 0);

	case BHND_DEVCLASS_SOFTMODEM:
		return ((sc->quirks & BWN_QUIRK_SOFTMODEM_UNPOPULATED) != 0);

	default:
		return (false);
	}
}