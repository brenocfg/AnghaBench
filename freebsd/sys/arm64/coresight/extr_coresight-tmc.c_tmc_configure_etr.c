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
typedef  int uint32_t ;
struct tmc_softc {int /*<<< orphan*/  res; } ;
struct endpoint {int dummy; } ;
struct TYPE_2__ {int low; int high; int bufsize; } ;
struct coresight_event {TYPE_1__ etr; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int AXICTL_AXCACHE_OS ; 
 int AXICTL_PROT_CTRL_BIT1 ; 
 int AXICTL_WRBURSTLEN_16 ; 
 int FFCR_EN_FMT ; 
 int FFCR_EN_TI ; 
 int FFCR_FON_FLIN ; 
 int FFCR_FON_TRIG_EVT ; 
 int FFCR_TRIGON_TRIGIN ; 
 int MODE_CIRCULAR_BUFFER ; 
 int STS_FULL ; 
 int STS_TMCREADY ; 
 int /*<<< orphan*/  TMC_AXICTL ; 
 int /*<<< orphan*/  TMC_DBAHI ; 
 int /*<<< orphan*/  TMC_DBALO ; 
 int /*<<< orphan*/  TMC_FFCR ; 
 int /*<<< orphan*/  TMC_MODE ; 
 int /*<<< orphan*/  TMC_RRP ; 
 int /*<<< orphan*/  TMC_RSZ ; 
 int /*<<< orphan*/  TMC_RWP ; 
 int /*<<< orphan*/  TMC_STS ; 
 int /*<<< orphan*/  TMC_TRG ; 
 int bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct tmc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tmc_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tmc_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tmc_configure_etr(device_t dev, struct endpoint *endp,
    struct coresight_event *event)
{
	struct tmc_softc *sc;
	uint32_t reg;

	sc = device_get_softc(dev);

	tmc_stop(dev);

	do {
		reg = bus_read_4(sc->res, TMC_STS);
	} while ((reg & STS_TMCREADY) == 0);

	/* Configure TMC */
	bus_write_4(sc->res, TMC_MODE, MODE_CIRCULAR_BUFFER);

	reg = AXICTL_PROT_CTRL_BIT1;
	reg |= AXICTL_WRBURSTLEN_16;

	/*
	 * SG operation is broken on DragonBoard 410c
	 * reg |= AXICTL_SG_MODE;
	 */

	reg |= AXICTL_AXCACHE_OS;
	bus_write_4(sc->res, TMC_AXICTL, reg);

	reg = FFCR_EN_FMT | FFCR_EN_TI | FFCR_FON_FLIN |
	    FFCR_FON_TRIG_EVT | FFCR_TRIGON_TRIGIN;
	bus_write_4(sc->res, TMC_FFCR, reg);

	bus_write_4(sc->res, TMC_TRG, 8);

	bus_write_4(sc->res, TMC_DBALO, event->etr.low);
	bus_write_4(sc->res, TMC_DBAHI, event->etr.high);
	bus_write_4(sc->res, TMC_RSZ, event->etr.bufsize / 4);

	bus_write_4(sc->res, TMC_RRP, event->etr.low);
	bus_write_4(sc->res, TMC_RWP, event->etr.low);

	reg = bus_read_4(sc->res, TMC_STS);
	reg &= ~STS_FULL;
	bus_write_4(sc->res, TMC_STS, reg);

	tmc_start(dev);

	return (0);
}