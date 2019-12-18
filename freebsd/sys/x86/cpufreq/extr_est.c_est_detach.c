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
struct est_softc {int /*<<< orphan*/  freq_list; scalar_t__ msr_settings; scalar_t__ acpi_settings; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int cpufreq_unregister (int /*<<< orphan*/ ) ; 
 struct est_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
est_detach(device_t dev)
{
	struct est_softc *sc;
	int error;

	error = cpufreq_unregister(dev);
	if (error)
		return (error);

	sc = device_get_softc(dev);
	if (sc->acpi_settings || sc->msr_settings)
		free(sc->freq_list, M_DEVBUF);
	return (0);
}