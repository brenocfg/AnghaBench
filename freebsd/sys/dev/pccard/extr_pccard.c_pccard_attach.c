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
struct TYPE_2__ {int /*<<< orphan*/  pf_head; } ;
struct pccard_softc {TYPE_1__ card; scalar_t__ sc_enabled_count; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct pccard_softc* PCCARD_SOFTC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int pccard_device_create (struct pccard_softc*) ; 

__attribute__((used)) static int
pccard_attach(device_t dev)
{
	struct pccard_softc *sc = PCCARD_SOFTC(dev);
	int err;

	sc->dev = dev;
	sc->sc_enabled_count = 0;
	if ((err = pccard_device_create(sc)) != 0)
		return  (err);
	STAILQ_INIT(&sc->card.pf_head);
	return (bus_generic_attach(dev));
}