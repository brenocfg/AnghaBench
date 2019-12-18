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
struct smist_softc {TYPE_1__* sets; void* dev; } ;
typedef  void* device_t ;
struct TYPE_2__ {int lat; void* dev; void* power; void* volts; void* freq; } ;

/* Variables and functions */
 void* CPUFREQ_VAL_UNKNOWN ; 
 int ENXIO ; 
 int /*<<< orphan*/  cpufreq_register (void*) ; 
 struct smist_softc* device_get_softc (void*) ; 
 scalar_t__ set_ownership (void*) ; 

__attribute__((used)) static int
smist_attach(device_t dev)
{
	struct smist_softc *sc;

	sc = device_get_softc(dev);
	sc->dev = dev;

	/* If we can't take ownership over BIOS, then bail out */
	if (set_ownership(dev) != 0)
		return (ENXIO);

	/* Setup some defaults for our exported settings. */
	sc->sets[0].freq = CPUFREQ_VAL_UNKNOWN;
	sc->sets[0].volts = CPUFREQ_VAL_UNKNOWN;
	sc->sets[0].power = CPUFREQ_VAL_UNKNOWN;
	sc->sets[0].lat = 1000;
	sc->sets[0].dev = dev;
	sc->sets[1] = sc->sets[0];

	cpufreq_register(dev);

	return (0);
}