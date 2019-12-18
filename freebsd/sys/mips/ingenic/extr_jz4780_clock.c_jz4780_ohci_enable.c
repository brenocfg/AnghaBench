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
typedef  int /*<<< orphan*/  uint32_t ;
struct jz4780_clock_softc {int dummy; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CGU_LOCK (struct jz4780_clock_softc*) ; 
 int /*<<< orphan*/  CGU_UNLOCK (struct jz4780_clock_softc*) ; 
 int /*<<< orphan*/  CSR_READ_4 (struct jz4780_clock_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct jz4780_clock_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JZ_OPCR ; 
 int /*<<< orphan*/  OPCR_SPENDN1 ; 
 int /*<<< orphan*/ * devclass_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct jz4780_clock_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jz4780_clock_devclass ; 

int
jz4780_ohci_enable(void)
{
	device_t dev;
	struct jz4780_clock_softc *sc;
	uint32_t reg;

	dev = devclass_get_device(jz4780_clock_devclass, 0);
	if (dev == NULL)
		return (-1);

	sc = device_get_softc(dev);
	CGU_LOCK(sc);

	/* Do not force port1 to suspend mode */
	reg = CSR_READ_4(sc, JZ_OPCR);
	reg |= OPCR_SPENDN1;
	CSR_WRITE_4(sc, JZ_OPCR, reg);

	CGU_UNLOCK(sc);
	return (0);
}