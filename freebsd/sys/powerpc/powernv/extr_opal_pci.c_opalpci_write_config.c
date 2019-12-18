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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u_int ;
struct opalpci_softc {int /*<<< orphan*/  phb_id; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  OPAL_EEH_ACTION_CLEAR_FREEZE_ALL ; 
 int OPAL_HARDWARE ; 
 int /*<<< orphan*/  OPAL_PCI_CONFIG_WRITE_BYTE ; 
 int /*<<< orphan*/  OPAL_PCI_CONFIG_WRITE_HALF_WORD ; 
 int /*<<< orphan*/  OPAL_PCI_CONFIG_WRITE_WORD ; 
 int /*<<< orphan*/  OPAL_PCI_DEFAULT_PE ; 
 int /*<<< orphan*/  OPAL_PCI_EEH_FREEZE_CLEAR ; 
 int OPAL_SUCCESS ; 
 struct opalpci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int opal_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,...) ; 

__attribute__((used)) static void
opalpci_write_config(device_t dev, u_int bus, u_int slot, u_int func,
    u_int reg, uint32_t val, int width)
{
	struct opalpci_softc *sc;
	uint64_t config_addr;
	int error = OPAL_SUCCESS;

	sc = device_get_softc(dev);

	config_addr = (bus << 8) | ((slot & 0x1f) << 3) | (func & 0x7);

	switch (width) {
	case 1:
		error = opal_call(OPAL_PCI_CONFIG_WRITE_BYTE, sc->phb_id,
		    config_addr, reg, val);
		break;
	case 2:
		error = opal_call(OPAL_PCI_CONFIG_WRITE_HALF_WORD, sc->phb_id,
		    config_addr, reg, val);
		break;
	case 4:
		error = opal_call(OPAL_PCI_CONFIG_WRITE_WORD, sc->phb_id,
		    config_addr, reg, val);
		break;
	}

	if (error != OPAL_SUCCESS) {
		/*
		 * Poking config state for non-existant devices can make
		 * the host bridge hang up. Clear any errors.
		 */
		if (error != OPAL_HARDWARE) {
			opal_call(OPAL_PCI_EEH_FREEZE_CLEAR,
			    sc->phb_id, OPAL_PCI_DEFAULT_PE,
			    OPAL_EEH_ACTION_CLEAR_FREEZE_ALL);
		}
	}
}