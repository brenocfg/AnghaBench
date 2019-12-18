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
struct pmcr_softc {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpufreq_register (int /*<<< orphan*/ ) ; 
 struct pmcr_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pmcr_attach(device_t dev)
{
	struct pmcr_softc *sc;

	sc = device_get_softc(dev);
	sc->dev = dev;

	cpufreq_register(dev);
	return (0);
}