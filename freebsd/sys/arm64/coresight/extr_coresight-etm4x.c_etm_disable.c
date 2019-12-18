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
 int /*<<< orphan*/  TRCSTATR ; 
 int TRCSTATR_IDLE ; 
 int bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct etm_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
etm_disable(device_t dev, struct endpoint *endp,
    struct coresight_event *event)
{
	struct etm_softc *sc;
	uint32_t reg;

	sc = device_get_softc(dev);

	/* Disable the trace unit */
	bus_write_4(sc->res, TRCPRGCTLR, 0);

	/* Wait for an IDLE bit */
	do {
		reg = bus_read_4(sc->res, TRCSTATR);
	} while ((reg & TRCSTATR_IDLE) == 0);
}