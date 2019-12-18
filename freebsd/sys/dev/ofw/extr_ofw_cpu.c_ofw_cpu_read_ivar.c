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
struct ofw_cpulist_softc {uintptr_t sc_addr_cells; } ;
struct ofw_cpu_softc {int /*<<< orphan*/  sc_reg; int /*<<< orphan*/  sc_reg_valid; int /*<<< orphan*/  sc_nominal_mhz; int /*<<< orphan*/  sc_cpu_pcpu; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
#define  CPU_IVAR_CPUID 131 
#define  CPU_IVAR_CPUID_SIZE 130 
#define  CPU_IVAR_NOMINAL_MHZ 129 
#define  CPU_IVAR_PCPU 128 
 int ENOENT ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ofw_cpu_read_ivar(device_t dev, device_t child, int index, uintptr_t *result)
{
	struct ofw_cpulist_softc *psc;
	struct ofw_cpu_softc *sc;

	sc = device_get_softc(dev);

	switch (index) {
	case CPU_IVAR_PCPU:
		*result = (uintptr_t)sc->sc_cpu_pcpu;
		return (0);
	case CPU_IVAR_NOMINAL_MHZ:
		if (sc->sc_nominal_mhz > 0) {
			*result = (uintptr_t)sc->sc_nominal_mhz;
			return (0);
		}
		break;
	case CPU_IVAR_CPUID_SIZE:
		psc = device_get_softc(device_get_parent(dev));
		*result = psc->sc_addr_cells;
		return (0);
	case CPU_IVAR_CPUID:
		if (sc->sc_reg_valid) {
			*result = (uintptr_t)sc->sc_reg;
			return (0);
		}
		break;
	}

	return (ENOENT);
}