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
typedef  scalar_t__ uint32_t ;
struct tmc_softc {scalar_t__ dev_type; struct coresight_event* event; int /*<<< orphan*/  nev; } ;
struct endpoint {int dummy; } ;
struct TYPE_2__ {int flags; } ;
struct coresight_event {TYPE_1__ etr; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ CORESIGHT_ETF ; 
 scalar_t__ CORESIGHT_ETR ; 
 int ETR_FLAG_ALLOCATE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ atomic_fetchadd_int (int /*<<< orphan*/ *,int) ; 
 struct tmc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tmc_configure_etr (int /*<<< orphan*/ ,struct endpoint*,struct coresight_event*) ; 
 int /*<<< orphan*/  tmc_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tmc_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tmc_enable(device_t dev, struct endpoint *endp,
    struct coresight_event *event)
{
	struct tmc_softc *sc;
	uint32_t nev;

	sc = device_get_softc(dev);

	if (sc->dev_type == CORESIGHT_ETF)
		return (0);

	KASSERT(sc->dev_type == CORESIGHT_ETR,
	    ("Wrong dev_type"));

	/*
	 * Multiple CPUs can call this same time.
	 * We allow only one running configuration.
	 */

	if (event->etr.flags & ETR_FLAG_ALLOCATE) {
		event->etr.flags &= ~ETR_FLAG_ALLOCATE;
		nev = atomic_fetchadd_int(&sc->nev, 1);
		if (nev == 0) {
			sc->event = event;
			tmc_stop(dev);
			tmc_configure_etr(dev, endp, event);
			tmc_start(dev);
		}
	}

	return (0);
}