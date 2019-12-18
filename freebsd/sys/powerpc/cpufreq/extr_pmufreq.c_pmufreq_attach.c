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
struct pmufreq_softc {int minfreq; int maxfreq; int curfreq; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  OF_getprop (int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  cpufreq_register (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct pmufreq_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pmufreq_attach(device_t dev)
{
	struct pmufreq_softc *sc;
	phandle_t node;

	sc = device_get_softc(dev);
	sc->dev = dev;

	node = ofw_bus_get_node(device_get_parent(dev));
	OF_getprop(node, "min-clock-frequency", &sc->minfreq, sizeof(sc->minfreq));
	OF_getprop(node, "max-clock-frequency", &sc->maxfreq, sizeof(sc->maxfreq));
	OF_getprop(node, "rounded-clock-frequency", &sc->curfreq, sizeof(sc->curfreq));
	sc->minfreq /= 1000000;
	sc->maxfreq /= 1000000;
	sc->curfreq /= 1000000;

	cpufreq_register(dev);
	return (0);
}