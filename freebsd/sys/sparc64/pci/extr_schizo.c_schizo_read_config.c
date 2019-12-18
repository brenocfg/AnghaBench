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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ u_int ;
struct TYPE_2__ {scalar_t__ sc_pci_secbus; } ;
struct schizo_softc {scalar_t__ sc_mode; TYPE_1__ sc_ops; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_REGMAX ; 
 scalar_t__ SCHIZO_MODE_SCZ ; 
 int /*<<< orphan*/  STX_CONF_OFF (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ STX_CS_DEVICE ; 
 scalar_t__ STX_CS_FUNC ; 
 struct schizo_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_pci_read_config_common (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static uint32_t
schizo_read_config(device_t dev, u_int bus, u_int slot, u_int func, u_int reg,
    int width)
{
	struct schizo_softc *sc;

	sc = device_get_softc(dev);
	/*
	 * The Schizo bridges contain a dupe of their header at 0x80.
	 */
	if (sc->sc_mode == SCHIZO_MODE_SCZ &&
	    bus == sc->sc_ops.sc_pci_secbus && slot == STX_CS_DEVICE &&
	    func == STX_CS_FUNC && reg + width > 0x80)
		return (0);

	return (ofw_pci_read_config_common(dev, PCI_REGMAX, STX_CONF_OFF(bus,
	    slot, func, reg), bus, slot, func, reg, width));
}