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
typedef  int uint32_t ;
struct tmc_softc {int /*<<< orphan*/  res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CTL_TRACECAPTEN ; 
 int STS_TMCREADY ; 
 int /*<<< orphan*/  TMC_CTL ; 
 int /*<<< orphan*/  TMC_STS ; 
 int bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct tmc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static int
tmc_start(device_t dev)
{
	struct tmc_softc *sc;
	uint32_t reg;

	sc = device_get_softc(dev);

	if (bus_read_4(sc->res, TMC_CTL) & CTL_TRACECAPTEN)
		return (-1);

	/* Enable TMC */
	bus_write_4(sc->res, TMC_CTL, CTL_TRACECAPTEN);
	if ((bus_read_4(sc->res, TMC_CTL) & CTL_TRACECAPTEN) == 0)
		panic("Not enabled\n");

	do {
		reg = bus_read_4(sc->res, TMC_STS);
	} while ((reg & STS_TMCREADY) == 1);

	if ((bus_read_4(sc->res, TMC_CTL) & CTL_TRACECAPTEN) == 0)
		panic("Not enabled\n");

	return (0);
}