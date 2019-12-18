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
struct funnel_softc {int /*<<< orphan*/  res; } ;
struct endpoint {int reg; } ;
struct coresight_event {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  FUNNEL_FUNCTL ; 
 int bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct funnel_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
funnel_disable(device_t dev, struct endpoint *endp,
    struct coresight_event *event)
{
	struct funnel_softc *sc;
	uint32_t reg;

	sc = device_get_softc(dev);

	reg = bus_read_4(sc->res, FUNNEL_FUNCTL);
	reg &= ~(1 << endp->reg);
	bus_write_4(sc->res, FUNNEL_FUNCTL, reg);
}