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
struct etm_softc {int /*<<< orphan*/  res; } ;
struct endpoint {int dummy; } ;
struct coresight_event {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRCPRGCTLR ; 
 int TRCPRGCTLR_EN ; 
 int /*<<< orphan*/  TRCSTATR ; 
 int TRCSTATR_IDLE ; 
 int bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct etm_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  etm_prepare (int /*<<< orphan*/ ,struct coresight_event*) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static int
etm_enable(device_t dev, struct endpoint *endp,
    struct coresight_event *event)
{
	struct etm_softc *sc;
	uint32_t reg;

	sc = device_get_softc(dev);

	etm_prepare(dev, event);

	/* Enable the trace unit */
	bus_write_4(sc->res, TRCPRGCTLR, TRCPRGCTLR_EN);

	/* Wait for an IDLE bit to be LOW */
	do {
		reg = bus_read_4(sc->res, TRCSTATR);
	} while ((reg & TRCSTATR_IDLE) == 1);

	if ((bus_read_4(sc->res, TRCPRGCTLR) & TRCPRGCTLR_EN) == 0)
		panic("etm is not enabled\n");

	return (0);
}