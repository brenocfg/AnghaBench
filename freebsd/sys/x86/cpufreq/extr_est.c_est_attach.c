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
struct est_softc {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  cpufreq_register (int /*<<< orphan*/ ) ; 
 struct est_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ est_get_info (int /*<<< orphan*/ ) ; 
 int mp_ncpus ; 
 int strict ; 

__attribute__((used)) static int
est_attach(device_t dev)
{
	struct est_softc *sc;

	sc = device_get_softc(dev);
	sc->dev = dev;

	/* On SMP system we can't guarantie independent freq setting. */
	if (strict == -1 && mp_ncpus > 1)
		strict = 0;
	/* Check CPU for supported settings. */
	if (est_get_info(dev))
		return (ENXIO);

	cpufreq_register(dev);
	return (0);
}