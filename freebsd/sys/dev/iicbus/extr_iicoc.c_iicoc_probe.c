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
struct iicoc_softc {int reg_shift; int /*<<< orphan*/  i2cfreq; int /*<<< orphan*/  clockfreq; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int /*<<< orphan*/  XLP_I2C_CLKFREQ ; 
 int /*<<< orphan*/  XLP_I2C_FREQ ; 
 struct iicoc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int pci_get_device (int /*<<< orphan*/ ) ; 
 int pci_get_vendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iicoc_probe(device_t dev)
{
	struct iicoc_softc *sc;
	
	sc = device_get_softc(dev);
	if ((pci_get_vendor(dev) == 0x184e) &&
	    (pci_get_device(dev) == 0x1011)) {
		sc->clockfreq = XLP_I2C_CLKFREQ;
		sc->i2cfreq = XLP_I2C_FREQ;
		sc->reg_shift = 2;
		device_set_desc(dev, "Netlogic XLP I2C Controller");
		return (BUS_PROBE_DEFAULT);
	}
	return (ENXIO);
}